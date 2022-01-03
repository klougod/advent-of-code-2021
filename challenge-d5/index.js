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
    x_and_y = line.split("->");

    input.push([
      x_and_y[0].split(",").map((n) => parseInt(n.replace(" ", ""))),
      x_and_y[1].split(",").map((n) => parseInt(n.replace(" ", ""))),
    ]);
  }

  return input;
}

function markHorizontalPoint(overlaps, equal_edge, edge1, edge2, isX = true) {
  if (edge1 < edge2) {
    for (let edge = edge1; edge <= edge2; edge++) {
      const index = isX ? `${equal_edge},${edge}` : `${edge},${equal_edge}`;
      const overlap = overlaps[index];

      if (overlap) {
        overlaps[index] = overlap + 1;
      } else {
        overlaps[index] = 1;
      }
    }
  } else {
    for (let edge = edge2; edge <= edge1; edge++) {
      const index = isX ? `${equal_edge},${edge}` : `${edge},${equal_edge}`;

      const overlap = overlaps[index];

      if (overlap) {
        overlaps[index] = overlap + 1;
      } else {
        overlaps[index] = 1;
      }
    }
  }
}

async function day1() {
  const overlaps = {};
  const input = await processLineByLine("input.txt");

  input.forEach((x_and_y) => {
    const [x1, y1] = x_and_y[0];
    const [x2, y2] = x_and_y[1];

    // HORIZONTAL
    if (x1 === x2) {
      markHorizontalPoint(overlaps, x1, y1, y2);
    }
    if (y1 === y2) {
      markHorizontalPoint(overlaps, y1, x1, x2, false);
    }
  });

  let count = 0;
  Object.keys(overlaps).forEach((i) => {
    if (overlaps[i] > 1) {
      count += 1;
    }
  });

  console.log("COUNT: ", count);
}

async function day2() {
  const overlaps = {};
  const input = await processLineByLine("input.txt");

  input.forEach((x_and_y) => {
    const [x1, y1] = x_and_y[0];
    const [x2, y2] = x_and_y[1];

    // Horizontal
    if (x1 === x2) {
      markHorizontalPoint(overlaps, x1, y1, y2);
    }
    if (y1 === y2) {
      markHorizontalPoint(overlaps, y1, x1, x2, false);
    }

    // Diagonal
    if (x1 < x2 && y1 < y2) {
      for (let x = x1, y = y1; x <= x2 && y <= y2; x++, y++) {
        const index = `${x},${y}`;
        const overlap = overlaps[index];

        if (overlap) {
          overlaps[index] = overlap + 1;
        } else {
          overlaps[index] = 1;
        }
      }
    }

    if (x1 > x2 && y1 > y2) {
      for (let x = x2, y = y2; x <= x1 && y <= y1; x++, y++) {
        const index = `${x},${y}`;
        const overlap = overlaps[index];

        if (overlap) {
          overlaps[index] = overlap + 1;
        } else {
          overlaps[index] = 1;
        }
      }
    }

    if (x1 > x2 && y1 < y2) {
      for (let x = x1, y = y1; x >= x2 && y <= y2; x--, y++) {
        const index = `${x},${y}`;
        const overlap = overlaps[index];

        if (overlap) {
          overlaps[index] = overlap + 1;
        } else {
          overlaps[index] = 1;
        }
      }
    }
    if (x1 < x2 && y1 > y2) {
      for (let x = x1, y = y1; x <= x2 && y >= y2; x++, y--) {
        const index = `${x},${y}`;
        const overlap = overlaps[index];

        if (overlap) {
          overlaps[index] = overlap + 1;
        } else {
          overlaps[index] = 1;
        }
      }
    }
  });

  let count = 0;
  Object.keys(overlaps).forEach((i) => {
    if (overlaps[i] > 1) {
      count += 1;
    }
  });

  console.log("COUNT: ", count);
}

day1();
day2();
