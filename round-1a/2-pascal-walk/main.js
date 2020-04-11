const fs = require("fs");

const io = fs.readFileSync(0).toString().split("\n");

const cases = Number(io.shift());

cases: for (let i = 1; i <= cases; ++i) {
  console.log("Case #" + i + ":");
  const N = Number(io.shift());
  if (N <= 500) {
    for (let i = 1; i <= N; ++i) {
      console.log(i, 1);
    }
  } else if (N <= 1000) {
    const jumps = (Math.sqrt(2 * N) - 1) | 0;
    console.log(1, 1);
    console.log(1, 2);
    let r = 1,
      k = 2,
      sum = 2;
    for (let i = 0; i < jumps; ++i) {
      ++r;
      sum += r;
      console.log(r, k);
    }
    --k;
    console.log(r, k);
    ++sum;
    while (sum < N) {
      ++r;
      ++sum;
      console.log(r, k);
    }
  }
}
