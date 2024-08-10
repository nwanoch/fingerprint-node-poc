// import express from "express";\
const express = require("express");

const ffi = require("ffi-napi");
// import path from "path";
const path = require("path");

// Path to your shared library
const libPath = path.resolve("mylib.so");

// Load the shared library
const myLib = ffi.Library(libPath, {
  sayHello: ["void", []], // Define the function signature
});

const app = express();

app.get("/", function (req, res) {
  // Call the C function
  myLib.sayHello();

  res.json({ message: "Hello World!" });
});

app.listen(3000, () => console.log("Listening on port 3000"));
