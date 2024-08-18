const express = require("express");
const addon = require("./build/Release/addon");

const app = express();
const port = 3000;

app.get("/", (req, res) => {
  const dllResult = addon.callDLL();
  res.send(`DLL function returned: ${dllResult}`);
});

app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}`);
});
