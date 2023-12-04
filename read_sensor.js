const http = require('http');
const fs = require('fs');
const readline = require('readline');

const port = parseInt(process.argv[2] || '3000');

let reading = {};

async function processLineByLine() {
  const fileStream = fs.createReadStream('/dev/ttyUSB0');

  const rl = readline.createInterface({
    input: fileStream,
    crlfDelay: Infinity
  });
  // Note: we use the crlfDelay option to recognize all instances of CR LF
  // ('\r\n') in input.txt as a single line break.

  for await (const line of rl) {
    // Each line in input.txt will be successively available here as `line`.
    reading = JSON.parse(line);
  }
}

processLineByLine();

http.createServer(function (req, res) {
    const body = JSON.stringify(reading) + '\n';
    res.writeHead(200, { 'Content-Type' : 'application/json', 'Content-Length' : body.length });
    res.end(body);
}).listen(port);

console.log("Serving on port:", port);

