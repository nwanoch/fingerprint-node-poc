const express = require("express");
const addon = require("./build/Release/addon");

const app = express();
const port = 3000;

app.get("/", (req, res) => {
  const result = addon.sayHello();
  const dllResult = addon.callDLL();
  res.send(`C++ function said: ${result}, DLL function returned: ${dllResult}`);
});

app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}`);
});
