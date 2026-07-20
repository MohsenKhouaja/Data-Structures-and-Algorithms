import { useMemo, useState } from "react";
import "./BinaryTreeViewer.css";

const NODE_RADIUS = 22;
const X_GAP = 70;
const Y_GAP = 96;
const PADDING = 52;

function extractArrayText(rawInput) {
  const trimmed = rawInput.trim();
  const open = trimmed.indexOf("[");
  const close = trimmed.lastIndexOf("]");

  if (open !== -1 || close !== -1) {
    if (open === -1 || close === -1 || close < open) {
      throw new Error("Use matching [ and ] brackets.");
    }

    return trimmed.slice(open + 1, close);
  }

  return trimmed;
}

function parseTreeArray(rawInput) {
  const arrayText = extractArrayText(rawInput);

  if (!arrayText.trim()) {
    return [];
  }

  return arrayText.split(",").map((item, index) => {
    const token = item.trim();
    const normalized = token.toLowerCase();

    if (["null", "nil", "none", "#"].includes(normalized)) {
      return null;
    }

    if (!/^-?\d+$/.test(token)) {
      throw new Error(`Invalid value at position ${index}: "${token}".`);
    }

    return Number(token);
  });
}

function buildTree(values) {
  if (!values.length || values[0] === null) {
    return null;
  }

  const root = { value: values[0], left: null, right: null };
  const queue = [root];
  let cursor = 1;

  while (queue.length && cursor < values.length) {
    const node = queue.shift();
    const leftValue = values[cursor++];

    if (leftValue !== undefined && leftValue !== null) {
      node.left = { value: leftValue, left: null, right: null };
      queue.push(node.left);
    }

    const rightValue = values[cursor++];

    if (rightValue !== undefined && rightValue !== null) {
      node.right = { value: rightValue, left: null, right: null };
      queue.push(node.right);
    }
  }

  return root;
}

function measure(node) {
  if (!node) {
    return 0;
  }

  node.width = Math.max(1, measure(node.left) + measure(node.right));
  return node.width;
}

function assignPositions(node, depth = 0, nextLeaf = { value: 0 }) {
  if (!node) {
    return;
  }

  assignPositions(node.left, depth + 1, nextLeaf);
  assignPositions(node.right, depth + 1, nextLeaf);

  if (!node.left && !node.right) {
    node.x = nextLeaf.value * X_GAP + PADDING;
    nextLeaf.value += 1;
  } else {
    const childXs = [node.left?.x, node.right?.x].filter((value) => value !== undefined);
    node.x = childXs.reduce((total, value) => total + value, 0) / childXs.length;
  }

  node.y = depth * Y_GAP + PADDING;
}

function flatten(node, depth = 0, nodes = [], edges = []) {
  if (!node) {
    return { nodes, edges, maxDepth: depth - 1 };
  }

  nodes.push(node);

  if (node.left) {
    edges.push({ from: node, to: node.left });
    flatten(node.left, depth + 1, nodes, edges);
  }

  if (node.right) {
    edges.push({ from: node, to: node.right });
    flatten(node.right, depth + 1, nodes, edges);
  }

  return {
    nodes,
    edges,
    maxDepth: Math.max(...nodes.map((item) => Math.round((item.y - PADDING) / Y_GAP))),
  };
}

function layoutTree(values) {
  const root = buildTree(values);

  if (!root) {
    return { nodes: [], edges: [], width: 520, height: 240 };
  }

  measure(root);
  assignPositions(root);

  const { nodes, edges, maxDepth } = flatten(root);
  const maxX = Math.max(...nodes.map((node) => node.x));

  return {
    nodes,
    edges,
    width: Math.max(520, maxX + PADDING),
    height: Math.max(240, (maxDepth + 1) * Y_GAP + PADDING),
  };
}

export default function BinaryTreeViewer({ values, updatedAt }) {
  const [treeValues, setTreeValues] = useState(values);
  const [inputValue, setInputValue] = useState(JSON.stringify(values));
  const [error, setError] = useState("");
  const layout = useMemo(() => layoutTree(treeValues), [treeValues]);

  function handleSubmit(event) {
    event.preventDefault();

    try {
      const nextValues = parseTreeArray(inputValue);
      setTreeValues(nextValues);
      setInputValue(JSON.stringify(nextValues));
      setError("");
    } catch (parseError) {
      setError(`${parseError.message} Use integers or null.`);
    }
  }

  return (
    <main className="tree-shell">
      <header className="tree-header">
        <div>
          <p className="eyebrow">LeetCode Level Order</p>
          <h1>Binary Tree Viewer</h1>
        </div>
        <div className="tree-meta">
          <span>{treeValues.length} slots</span>
          <span>{treeValues.filter((value) => value !== null).length} nodes</span>
        </div>
      </header>

      <form className="tree-input-panel" onSubmit={handleSubmit}>
        <label htmlFor="tree-array">Tree array</label>
        <div className="tree-input-row">
          <input
            id="tree-array"
            type="text"
            value={inputValue}
            onChange={(event) => setInputValue(event.target.value)}
            spellCheck="false"
            placeholder="[6,2,8,0,4,7,9,null,null,3,5]"
            aria-invalid={error ? "true" : "false"}
            aria-describedby={error ? "tree-input-error" : undefined}
          />
          <button type="submit">Render</button>
        </div>
        {error ? (
          <p className="tree-input-error" id="tree-input-error">
            {error}
          </p>
        ) : null}
      </form>

      <section className="tree-stage" aria-label="Rendered binary tree">
        {layout.nodes.length ? (
          <svg
            role="img"
            viewBox={`0 0 ${layout.width} ${layout.height}`}
            className="tree-svg"
            aria-label={`Binary tree rendered from ${JSON.stringify(treeValues)}`}
          >
            <g className="tree-edges">
              {layout.edges.map((edge, index) => (
                <line
                  key={`${edge.from.value}-${edge.to.value}-${index}`}
                  x1={edge.from.x}
                  y1={edge.from.y + NODE_RADIUS}
                  x2={edge.to.x}
                  y2={edge.to.y - NODE_RADIUS}
                />
              ))}
            </g>
            <g className="tree-nodes">
              {layout.nodes.map((node, index) => (
                <g key={`${node.value}-${index}`} transform={`translate(${node.x} ${node.y})`}>
                  <circle r={NODE_RADIUS} />
                  <text dominantBaseline="middle" textAnchor="middle">
                    {node.value}
                  </text>
                </g>
              ))}
            </g>
          </svg>
        ) : (
          <div className="empty-tree">Empty tree</div>
        )}
      </section>

      <footer className="tree-footer">
        <code>{JSON.stringify(treeValues)}</code>
        <time dateTime={updatedAt}>{new Date(updatedAt).toLocaleString()}</time>
      </footer>
    </main>
  );
}
