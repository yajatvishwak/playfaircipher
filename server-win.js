const express = require("express");
const bodyParser = require("body-parser");
const cors = require("cors");
const app = express();
var fs = require("fs");

const { exec, spawn } = require("child_process");
const bat = spawn("cmd.exe", ["/c", "my.bat"]);

app.use(cors());
app.use(bodyParser.json());

app.get("/p", (req, res) => res.json("Hello World!"));

app.post("/", (req, res) => {
  console.log(req.body);
  var writeStream = fs.createWriteStream("code.bat");
  var code = `cmd "alog ${req.body.type} "${req.body.message}" "${req.body.key}" "`;
  writeStream.write(code);
  writeStream.end();

  exec("code.bat", (err, stdout, stderr) => {
    if (err) {
      console.error(err);
      return err;
    }
    console.log(stdout);
    res.json({ output: stdout });
  });
});
app.listen(3000, () => console.log("Server at 3000"));
