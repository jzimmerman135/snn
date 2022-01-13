buttons.dragMode.addEventListener('click', dragMode);
buttons.clickMode.addEventListener('click', clickMode);
buttons.connectMode.addEventListener('click', connectMode);
buttons.cutMode.addEventListener('click', cutMode);
buttons.add.addEventListener('click', addNeuron);

buttons.play.addEventListener('click', play);
buttons.pause.addEventListener('click', pause);

var board = document.getElementById('board');

var connectionSvg = document.createElementNS('http://www.w3.org/2000/svg', 'svg');
connectionSvg.classList.add('connectionSVG');
board.appendChild(connectionSvg);

function setDefault() {
    // addNeuron();
    return;
}

function dragMode() {
    uncheckAllBut("dragMode");
    for (let i = 0; i < neurons.length; i++) {
        neurons[i].setDragMode();
    }
    return;
}

function clickMode() {
    uncheckAllBut("clickMode");
    for (let i = 0; i < neurons.length; i++) {
        neurons[i].setClickMode();
    }
    for (let i = 0; i < connections.length; i++) {
        connections[i].setClickMode();
    }
}

function connectMode() {
    uncheckAllBut("connectMode");
    for (let i = 0; i < neurons.length; i++) {
        neurons[i].setConnectMode();
    }
    return;
}

function cutMode() {
    uncheckAllBut("cutMode");
    for (let i = 0; i < connections.length; i++) {
        connections[i].setCutMode();
    }
    return;
}

function idleConnections() {
    for (let i = 0; i < connections.length; i++) {
        connections[i].setIdleMode();
    }
}

function idleNeurons() {
    for (let i = 0; i < neurons.length; i++) {
        neurons[i].setIdleMode();
    }
}

function addNeuron() {
    let newNeuron = new Neuron();
    let i = 0;
    newNeuron.shiftRight(i);
    while (positionOccupied(newNeuron)) {
        newNeuron.shiftRight(++i);
    }
    neurons.push(newNeuron);
    dragMode();
}

function positionOccupied(neuron) {
    for (let i = 0; i < neurons.length; i++) {
        if (neurons[i].getInputPointLeft() == neuron.getInputPointLeft() &&
            neurons[i].getInputPointTop() == neuron.getInputPointTop()) {
            return true;
        }
    }
    return false;
}

function uncheckAllBut(name) {
    buttons.dragMode.checked = false;
    buttons.clickMode.checked = false;
    buttons.connectMode.checked = false;
    buttons.cutMode.checked = false;
    buttons[name].checked = true;
    idleConnections();
    idleNeurons();
}

function play() {
    document.getElementById('demoBox').style.top = neurons[1].getInputPointTop() + "px";
    document.getElementById('demoBox').style.left = neurons[1].getInputPointLeft() + "px";
}

function pause() {
    document.getElementById('demoBox').style.top = neurons[1].getOutputPointTop() + "px";
    document.getElementById('demoBox').style.left = neurons[1].getOutputPointLeft() + "px";
}

function max(a, b) {
    return a * (a >= b) + b * (a < b);
}

function min(a, b) {
    return a * (a <= b) + b * (a > b);
}
