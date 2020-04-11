const fs = require("fs");

const io = fs.readFileSync(0).toString().split("\n");

const cases = Number(io.shift());

cases: for (let i = 1; i <= cases; ++i) {
  fs.appendFileSync(1, "Case #" + i + ": ");
  const N = Number(io.shift());
  const patterns = io.splice(0, N);
  let start = "",
    end = "";
  for (let p of patterns) {
    if (p.startsWith("*")) {
      p = p.substr(1, p.length - 1);
      if (end.endsWith(p)) {
      } else if (p.endsWith(end)) {
        end = p;
      } else {
        console.log("*");
        continue cases;
      }
    } else if (p.endsWith("*")) {
      p = p.substr(0, p.length - 1);
      if (start.startsWith(p)) {
      } else if (p.startsWith(start)) {
        start = p;
      } else {
        console.log("*");
        continue cases;
      }
    }
  }
  let out = "";
  while (out.length < start.length) {
    if ((out + end).startsWith(start)) {
      out = out + end;
      if (out.length <= 10000) console.log(out);
      else console.log("*");
      continue cases;
    } else {
      out = start.substr(0, out.length + 1);
    }
  }
  out = start + end;
  if (out.length <= 10000) console.log(out);
  else console.log("*");
}
