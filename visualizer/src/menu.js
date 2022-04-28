buttons.dragMode.addEventListener('click', dragMode);
buttons.clickMode.addEventListener('click', clickMode);
buttons.connectMode.addEventListener('click', connectMode);
buttons.cutMode.addEventListener('click', cutMode);
buttons.deleteMode.addEventListener('click', deleteMode);
buttons.add.addEventListener('click', addNeuron);

buttons.play.addEventListener('click', play);

var board = document.getElementById('board');

var connectionSvg = document.createElementNS('http://www.w3.org/2000/svg', 'svg');
connectionSvg.classList.add('connectionSVG');
board.appendChild(connectionSvg);

const NUM_INPUTS_START = 4;
const NUM_NEURONS_START = 3;

function setDefault() {
    for (let i = 0; i < NUM_NEURONS_START; i++) {
        addNeuron();
    }
    for (let i = 0; i < NUM_INPUTS_START; i++) {
        new InputNeuron();
    }
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
    for (let i = 0; i < inputNeurons.length; i++) {
        inputNeurons[i].setClickMode();
    }
}

function connectMode() {
    uncheckAllBut("connectMode");
    for (let i = 0; i < neurons.length; i++) {
        neurons[i].setConnectMode();
    }
    for (let i = 0; i < inputNeurons.length; i++) {
        inputNeurons[i].setConnectMode();
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

function deleteMode() {
    uncheckAllBut("deleteMode");
    for (let i = 0; i < neurons.length; i++) {
        neurons[i].setDeleteMode();
    }
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

function idleInputs() {
    for (let i = 0; i < inputNeurons.length; i++) {
        inputNeurons[i].setIdleMode();
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


function uncheckAllBut(name) {
    buttons.dragMode.checked = false;
    buttons.clickMode.checked = false;
    buttons.connectMode.checked = false;
    buttons.cutMode.checked = false;
    buttons.deleteMode.checked = false;
    buttons[name].checked = true;
    idleConnections();
    idleNeurons();
    idleInputs();
}

function play() {
    for (let i = 0; i < inputNeurons.length; i++) {
        inputNeurons[i].oscillate(500 * (i + 1));
    }
    buttons.play.removeEventListener('click', play);
    buttons.play.addEventListener('click', pause);
}

function pause() {
    console.log("made it")
    for (let i = 0; i < inputNeurons.length; i++) {
        inputNeurons[i].stopOscillating();
    }
    buttons.play.removeEventListener('click', pause);
    buttons.play.addEventListener('click', play);
}

function max(a, b) {
    return a * (a >= b) + b * (a < b);
}

function min(a, b) {
    return a * (a <= b) + b * (a > b);
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

function placeInputNeurons() {
    for (let i = 0; i < inputNeurons.length; i++) {
        inputNeurons[i].reposition(i);
    }
}