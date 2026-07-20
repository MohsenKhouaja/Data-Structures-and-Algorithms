#!/usr/bin/env node

import { mkdir, readFile, writeFile } from "node:fs/promises";
import { execFileSync, spawn } from "node:child_process";
import readline from "node:readline/promises";
import { stdin as input, stdout as output } from "node:process";

const DATA_PATH = new URL("../src/data/tree-input.json", import.meta.url);

function extractArrayText(rawInput) {
  const trimmed = rawInput.trim();
  const open = trimmed.indexOf("[");
  const close = trimmed.lastIndexOf("]");

  if (open !== -1 || close !== -1) {
    if (open === -1 || close === -1 || close < open) {
      throw new Error("Array input must contain matching [ and ] brackets.");
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
      throw new Error(`Invalid value at position ${index}: "${token}". Use integers or null.`);
    }

    return Number(token);
  });
}

function readInputArg(args) {
  for (let index = 0; index < args.length; index += 1) {
    const arg = args[index];

    if (arg === "-h" || arg === "--help") {
      return { help: true };
    }

    if (arg === "-i" || arg === "--input") {
      const value = args[index + 1];

      if (!value) {
        throw new Error(`${arg} requires an array value.`);
      }

      return { value };
    }

    if (arg.startsWith("--input=")) {
      return { value: arg.slice("--input=".length) };
    }

    if (!arg.startsWith("-")) {
      return { value: arg };
    }

    throw new Error(`Unknown option: ${arg}`);
  }

  return { value: null };
}

function printHelp() {
  console.log(`Usage:
  tree -i "[6,2,8,0,4,7,9,null,null,3,5]"
  tree --input "root = [1,2,3,null,4]"
  tree

When no input is provided, press Enter at the prompt to reuse the saved tree.`);
}

async function readSavedValues() {
  try {
    const saved = JSON.parse(await readFile(DATA_PATH, "utf8"));
    return Array.isArray(saved.values) ? saved.values : [];
  } catch {
    return [];
  }
}

async function promptForArray() {
  const rl = readline.createInterface({ input, output });

  try {
    const answer = await rl.question("Tree array (Enter to reuse saved): ");

    if (!answer.trim()) {
      return readSavedValues();
    }

    return parseTreeArray(answer);
  } finally {
    rl.close();
  }
}

async function saveTreeArray(values) {
  await mkdir(new URL("../src/data/", import.meta.url), { recursive: true });
  await writeFile(
    DATA_PATH,
    `${JSON.stringify({ values, updatedAt: new Date().toISOString() }, null, 2)}\n`,
    "utf8",
  );
}

function openBrowser(url) {
  const command =
    process.platform === "darwin" ? "open" : process.platform === "win32" ? "cmd" : "xdg-open";
  const args = process.platform === "win32" ? ["/c", "start", "", url] : [url];

  const child = spawn(command, args, {
    detached: true,
    stdio: "ignore",
  });

  child.unref();
}

function getRunningAstroUrl() {
  try {
    const status = execFileSync("npm", ["exec", "astro", "dev", "status"], {
      encoding: "utf8",
      stdio: ["ignore", "pipe", "ignore"],
    });
    const message = JSON.parse(status).message ?? "";
    return message.match(/https?:\/\/[^\s,)]+/)?.[0] ?? null;
  } catch {
    return null;
  }
}

function startAstro() {
  const runningUrl = getRunningAstroUrl();

  if (runningUrl) {
    console.log(`\nTree saved. Opening existing Astro viewer at ${runningUrl}\n`);
    openBrowser(runningUrl);
    return;
  }

  console.log("\nTree saved. Starting Astro viewer and opening your browser.\n");

  const child = spawn("npm", ["run", "dev", "--", "--host", "127.0.0.1", "--open"], {
    stdio: "inherit",
  });

  child.on("exit", (code, signal) => {
    if (signal) {
      process.kill(process.pid, signal);
      return;
    }

    process.exit(code ?? 0);
  });
}

try {
  const args = readInputArg(process.argv.slice(2));

  if (args.help) {
    printHelp();
    process.exit(0);
  }

  const values = args.value === null ? await promptForArray() : parseTreeArray(args.value);
  await saveTreeArray(values);
  startAstro();
} catch (error) {
  console.error(`\n${error.message}`);
  process.exit(1);
}
