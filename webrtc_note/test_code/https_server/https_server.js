'use strict'

var https = require('https');
var fs = require('fs');

var options = {
    key  : fs.readFileSync('./cert/server.key'),
    cert : fs.readFileSync('./cert/server.pem')
}

var app = https.createServer(options, function(req, res){
    res.writeHead(200, {'Content-Type':'text/plain'});
    res.end('Hello Mr.Miaow!\n');
}).listen(443, '0.0.0.0');
