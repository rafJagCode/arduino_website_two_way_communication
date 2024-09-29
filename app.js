const http = require('http');
const fs = require('fs');
const SerialPort = require("serialport");
const { Server } = require('socket.io');

const parsers = SerialPort.parsers;

const parser = new parsers.Readline({
	delimeter: '/r/n'
});

let port = new SerialPort('COM3', {
	baudRate: 9600,
	dataBits: 8,
	parity: 'none',
	stopBits: 1,
	flowControl: false
});

port.pipe(parser);


const index = fs.readFileSync('index.html');
const app = http.createServer((req, res)=>{
	res.writeHead(200, {'Content-Type': 'text/html'});
	res.end(index);
});

const io = new Server(app);
parser.on('data', (data) =>{
	io.emit('data', data);
	port.write(data + '\n');
});
io.on('connection', (socket) => {
	socket.on('webdata', (webdata)=>{
		port.write(webdata + '\n');
	});
});

app.listen(3000);