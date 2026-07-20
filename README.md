# Data Structures and Algorithms

A personal collection of C++ implementations for various data structures and algorithm problems. This repository serves as practice for coding interviews and competitive programming, featuring solutions from NeetCode 150, segment tree implementations, and classic algorithmic challenges.

## Purpose

- 🎯 Coding interview preparation
- 💡 Algorithm problem-solving practice
- 🧠 Data structure implementation and understanding
- 🏆 Competitive programming training

## Binary tree viewer

Install the web dependencies once:

```bash
npm install
```

Then start the prompt-driven tree viewer:

```bash
npm run tree
```

Paste a LeetCode-style level-order array such as:

```txt
[6,2,8,0,4,7,9,null,null,3,5]
```

You can also pass the array directly:

```bash
npm run tree -- -i "[6,2,8,0,4,7,9,null,null,3,5]"
```

For a bare `tree -i ...` command, link the package once from this repo:

```bash
npm link
tree -i "[6,2,8,0,4,7,9,null,null,3,5]"
```

When no input is provided, press Enter at the prompt to reuse the saved tree. The command writes the array to `src/data/tree-input.json`, starts Astro on an available local port, and opens the browser automatically.
