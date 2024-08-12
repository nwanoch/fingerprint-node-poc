const express = require("express");
const addon = require("./build/Release/addon");

const app = express();
const port = 3000;

app.get("/", (req, res) => {
  const result = addon.sayHello();
  res.send(`C++ function said: ${result}`);
});

app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}`);
});
