const fs = require("fs");
const readline = require("readline");

async function processLineByLine(file) {
  const input = [];

  const fileStream = fs.createReadStream(file);

  const rl = readline.createInterface({
    input: fileStream,
    crlfDelay: Infinity,
  });

  for await (const line of rl) {
    input.push(line.split("|").map((s) => s.trim()));
  }

  return input;
}

const countDigits = {
  2: 1,
  4: 4,
  3: 7,
  7: 8,
};

async function day1() {
  const input = await processLineByLine("input.txt");
  let uniques = 0;

  input.forEach(([_entry, output]) => {
    const outputDigits = output.split(" ");

    for (digit of outputDigits) {
      const uniqueCount = countDigits[digit.length];
      if (uniqueCount) {
        uniques++;
      }
    }
  });

  console.log("Unique: ", uniques);
}

async function day2() {
  const input = await processLineByLine("input.txt");
  const counts = [];

  input.forEach(([entry, output]) => {
    const outputDigits = output.split(" ");
    const entryDigits = entry.split(" ");

    const entryHelper = {};
    const outputHelper = {};

    // find uniques
    for (digit of entryDigits) {
      const uniqueCount = countDigits[digit.length];
      if (uniqueCount) {
        entryHelper[uniqueCount] = digit;
      }
    }

    // find 6
    for (digit of entryDigits) {
      const digits7 = entryHelper[7].split("");
      if (digit.length === 6) {
        const found = digits7.every((d) => digit.includes(d));
        if (!found) {
          entryHelper[6] = digit;
        }
      }
    }

    // find 9, 3 and 5
    for (digit of entryDigits) {
      const digits4 = entryHelper[4].split("");
      const digits7 = entryHelper[7].split("");
      const digits6 = entryHelper[6];

      if (digit.length === 6) {
        // find 9
        const found9 = digits4.every((d) => digit.includes(d));
        if (found9) {
          entryHelper[9] = digit;
        }
      }
      if (digit.length === 5) {
        // find 3
        const found3 = digits7.every((d) => digit.includes(d));
        if (found3) {
          entryHelper[3] = digit;
        }
        // find 5
        const found5 = digit.split("").every((d) => digits6.includes(d));
        if (found5) {
          entryHelper[5] = digit;
        }
      }
    }

    Object.keys(entryHelper).forEach((key) => {
      const entryHelp = entryHelper[key];
      outputHelper[entryHelp] = key;
    });

    // find 0 and 2
    for (digit of entryDigits) {
      if (digit.length === 6) {
        const found = outputHelper[digit];
        if (!found) {
          entryHelper[0] = digit;
        }
      }
      if (digit.length === 5) {
        const found = outputHelper[digit];
        if (!found) {
          entryHelper[2] = digit;
        }
      }
    }

    Object.keys(entryHelper).forEach((key) => {
      const entryHelp = entryHelper[key];
      outputHelper[entryHelp] = key;
    });

    let outCode = "";
    for (outputDigit of outputDigits) {
      const keys = Object.keys(outputHelper);
      for (k of keys) {
        const ks = k.split("");
        const ot = outputDigit.split("");
        if (ks.length === ot.length) {
          if (ks.every((kv) => ot.includes(kv))) {
            outCode += outputHelper[k];
            break;
          }
        }
      }
    }

    counts.push(parseInt(outCode));
  });

  console.log(
    "\nTotal count: ",
    counts.reduce((p, c) => p + c, 0)
  );
}

day1();
day2();
