const express = require('express');
const http = require('http');
const socketIo = require('socket.io');
const path = require('path');
const bodyParser = require('body-parser'); // Pour parser les requêtes POST

const app = express();
const server = http.createServer(app);
const io = socketIo(server);

const PORT = process.env.PORT || 3000;

app.use(bodyParser.json()); // Supporte le parsing de JSON
app.use(express.static('public'));

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'index.html'));
});

io.on('connection', (socket) => {
    console.log('New client connected');
    socket.on('disconnect', () => {
        console.log('Client disconnected');
    });
});

// Recevoir les données du capteur ESP32
app.post('/sensor-data', (req, res) => {
    console.log('Data received:', req.body);
    // Émettre les données aux clients en temps réel
    io.emit('FromAPI', req.body);
    res.status(200).send('Data received');
});

server.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`);
});
