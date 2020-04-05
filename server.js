const express = require("express");
const bodyParser = require("body-parser");
const { exec } = require("child_process");
const cors = require("cors");
const app = express();
app.use(cors());
app.use(bodyParser.json());

app.get("/p", (req, res) => res.json("Hello World!"));

app.post("/", (req, res) => {
  console.log(req.body);

  let code =
    "./alog " +
    req.body.type +
    ' "' +
    req.body.message +
    '" "' +
    req.body.key +
    '"';
  exec(code, (err, stdout, stderr) => {
    if (err) {
      return err;
    }
    res.json({ output: stdout });
  });
});
app.listen(3000, () => console.log("Server at 3000"));
