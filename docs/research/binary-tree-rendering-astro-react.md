# Rendering LeetCode Level-Order Binary Trees in Astro/React

Date: 2026-07-10

## Question

Determine the best current, primary-source-backed approach for rendering a binary tree from a LeetCode-style level-order array in a local HTML/React/Astro UI.

## Recommendation

Use an Astro page with the official React integration and render a small React island that converts the level-order array into an explicit hierarchical object, then passes that hierarchy to `react-d3-tree`.

This is the best default for a local interview-practice UI because:

- Astro officially supports React components through `@astrojs/react`, which enables rendering and client-side hydration for React components. Source: Astro `@astrojs/react` docs, lines 321-325, https://docs.astro.build/en/guides/integrations-guide/react/
- Interactive tree controls should be hydrated as a client component. Astro's `client:load` hydrates immediately for visible interactive UI, while `client:only="react"` skips server rendering and renders only in the browser. Source: Astro directive docs, lines 461-469 and 524-530, https://docs.astro.build/en/reference/directives-reference/
- `react-d3-tree` is a purpose-built React component for hierarchical tree graphs. Its own README says it represents hierarchical data as an interactive tree graph using D3's tree layout, and its required data prop uses a recursive `children` hierarchy. Source: `react-d3-tree` README, lines 281-289 and 376-389, https://github.com/bkrem/react-d3-tree
- The current npm package metadata for `react-d3-tree` is version `3.6.6`, has React 16/17/18/19 peer support, and depends on D3 hierarchy/selection/shape/zoom packages. Source: npm registry package metadata, https://registry.npmjs.org/react-d3-tree/latest

## Data Conversion

Do not try to draw directly from the array. Convert once into a tree-shaped object with stable IDs:

```ts
type LevelValue = string | number | null;

type VisualNode = {
  id: string;
  name: string;
  index: number;
  children?: VisualNode[];
};

function levelOrderToTree(values: LevelValue[]): VisualNode | null {
  if (values.length === 0 || values[0] == null) return null;

  const nodes = values.map((value, index) =>
    value == null
      ? null
      : {
          id: String(index),
          name: String(value),
          index,
          children: [] as VisualNode[],
        },
  );

  for (let index = 0; index < nodes.length; index += 1) {
    const node = nodes[index];
    if (!node) continue;

    const left = nodes[2 * index + 1];
    const right = nodes[2 * index + 2];

    if (left) node.children.push(left);
    if (right) node.children.push(right);
    if (node.children.length === 0) delete node.children;
  }

  return nodes[0];
}
```

Notes:

- Preserve array index as `id`/metadata. React recommends stable keys in data rather than generating keys during render, because keys let React match items across updates. Source: React rendering lists docs, lines 310-317, https://react.dev/learn/rendering-lists
- If the UI lets users edit the input array, memoize the conversion from parsed array to hierarchy. React's `useMemo` caches a calculation between re-renders until dependencies change, and React explicitly frames it as a performance optimization. Source: React `useMemo` docs, lines 184-187 and 265-289, https://react.dev/reference/react/useMemo
- For LeetCode-style arrays, `null` positions should not create visible nodes. They only reserve index positions so children still map by `left = 2i + 1` and `right = 2i + 2`.

## React/Astro Shape

Recommended usage:

```astro
---
import BinaryTreeViewer from '../components/BinaryTreeViewer.tsx';
---

<BinaryTreeViewer client:load initialValues={[3, 9, 20, null, null, 15, 7]} />
```

In the React component:

```tsx
import { useMemo } from 'react';
import Tree from 'react-d3-tree';

export function BinaryTreeViewer({ initialValues }: { initialValues: LevelValue[] }) {
  const data = useMemo(() => levelOrderToTree(initialValues), [initialValues]);

  if (!data) return null;

  return (
    <div style={{ width: '100%', height: 480 }}>
      <Tree
        data={data}
        orientation="vertical"
        collapsible={false}
        pathFunc="elbow"
      />
    </div>
  );
}
```

`react-d3-tree` documents that `<Tree />` fills the width and height of its container, that `data` is the only required prop, and that node objects can nest child nodes under `children`. Source: `react-d3-tree` README, lines 356-368 and 376-389, https://github.com/bkrem/react-d3-tree

Use `client:load` for the first viewport tree viewer. Use `client:only="react"` if the tree library accesses browser-only APIs during server rendering or if hydration mismatches appear. Astro documents `client:only` as skipping HTML server rendering and requiring the framework name because Astro does not run the component on the server. Source: Astro directive docs, lines 524-530, https://docs.astro.build/en/reference/directives-reference/

## Library Options

### Option A: `react-d3-tree`

Best default.

Strengths:

- Directly accepts recursive tree data with `name`, optional `attributes`, and optional `children`. Source: `react-d3-tree` README, lines 376-389, https://github.com/bkrem/react-d3-tree
- Built-in interaction and styling hooks: default nodes/links, node class props, `pathClassFunc`, event handlers, custom node rendering, and configurable link path functions. Source: `react-d3-tree` README, lines 390-487, https://github.com/bkrem/react-d3-tree
- Lowest implementation cost for a local UI.

Risks/tradeoffs:

- It is an opinionated SVG tree component. If the UI later needs pixel-perfect layout, custom edge routing, or advanced keyboard/accessibility behavior, direct rendering may become cleaner.
- Its docs site currently labels v3.6.5, while npm latest is v3.6.6. Treat npm metadata as the package version source and README/API docs as behavioral guidance. Sources: docs, https://bkrem.github.io/react-d3-tree/docs/ and npm metadata, https://registry.npmjs.org/react-d3-tree/latest

### Option B: `@visx/hierarchy` plus explicit SVG nodes/links

Good when the app needs custom rendering control.

Strengths:

- `@visx/hierarchy` provides React components for hierarchical visualizations and largely mirrors `d3-hierarchy`; it also exports the `hierarchy` utility. Source: visx hierarchy docs, lines 55-64, https://vx-demo.vercel.app/docs/hierarchy
- Its `Tree` component takes a required root `HierarchyNode`, plus configurable node/link components, `nodeSize`, `separation`, and `size`. Source: visx hierarchy docs, lines 218-251, https://vx-demo.vercel.app/docs/hierarchy
- Current npm metadata for `@visx/hierarchy` is version `4.0.0`, with React 18/19 peer support. Source: npm registry package metadata, https://registry.npmjs.org/@visx%2fhierarchy/latest

Risks/tradeoffs:

- More code than `react-d3-tree`: you must render labels, circles, links, sizing, controls, and empty states yourself.
- Better for a polished custom visualization than for a quick local LeetCode helper.

### Option C: Direct `d3-hierarchy`

Good only if avoiding React tree libraries or building a fully custom SVG/canvas renderer.

D3's `hierarchy(data)` constructs a root node from hierarchical data and defaults to reading children from `d.children`. Its `tree(root)` layout assigns `x` and `y` coordinates to the root and descendants, and uses the Reingold-Tilford tidy tree algorithm. Sources: D3 hierarchy docs, lines 251-280 and 291-318, https://d3js.org/d3-hierarchy/hierarchy; D3 tree docs, lines 251-263, https://d3js.org/d3-hierarchy/tree

Current npm metadata for `d3-hierarchy` is version `3.1.2`. Source: npm registry package metadata, https://registry.npmjs.org/d3-hierarchy/latest

## Implementation Guidance

1. Parse the user input as JSON or as a comma-separated fallback, normalizing `null`, `undefined`, empty slots, and `"null"` to `null`.
2. Validate early: require an array, allow numbers/strings/null, and show parse errors next to the input.
3. Convert the normalized array to `VisualNode | null` using array-index child mapping.
4. Render a fixed-height responsive container around `<Tree />`; the library expects container dimensions.
5. Use stable metadata (`id`, `index`, maybe `arrayPath`) for node labels, React keys in custom renderers, and debugging.
6. Start with `react-d3-tree` defaults, `collapsible={false}`, and a simple `pathFunc` such as `elbow` or `straight` for algorithm visual clarity.
7. Move to visx/direct D3 only if the app needs custom rendering beyond what `renderCustomNodeElement`, node class props, link class props, and `pathFunc` can cover.

## Decision

Adopt `react-d3-tree` for the first implementation. It matches the input after a small deterministic adapter, handles tree layout and interaction without bespoke D3 code, works with current React peer ranges, and fits Astro as a hydrated React island. Keep the conversion function library-agnostic so the renderer can be swapped to visx or direct D3 later without changing parsing or tree construction.
