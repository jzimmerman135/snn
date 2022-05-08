var ioDiv = document.getElementById('ioDiv');
const RADIUS = 20;
class InputNeuron {
    constructor() {
        this.outputs = [];
        this.output = 0;
        this.buildInputNeuron();
        inputNeurons.push(this);
        placeInputNeurons();
    }    

    reposition(index) {
        let rect = board.getBoundingClientRect();
        let inputSvgRect = this.inputSvg.getBoundingClientRect();
        this.inputSvg.style.top = ++index * (rect.height - inputSvgRect.height) / (inputNeurons.length + 1);        
    }

    getOutputPointLeft() {
        let rect = this.inputSvg.getBoundingClientRect();
        return rect.left + rect.width * (3 / 4) - 5;
    }

    getOutputPointTop() {
        let rect = this.inputSvg.getBoundingClientRect();
        return rect.top + rect.height * (1 / 2) - 5;
    }

    spike(val) {
        this.spikeCircle.setAttribute('r', RADIUS);
        this.inputSpikeLine.style.strokeWidth = 7;

        this.output = val;

        for (let i = 0; i < this.outputs.length; i++) {
            this.outputs[i].sendData(this.output);
        }

        setTimeout(() => {
            this.spikeCircle.setAttribute('r', '0');
            this.inputSpikeLine.style.strokeWidth = 0;
        }, 200);
    }

    setClickMode() {
        this.inputSvg.onclick = () => {
            this.spike(1);
        }
    }

    setConnectMode() {
        this.inputSvg.onclick = () => {
            new Connection(this);
        }
    }

    setIdleMode() {
        this.inputSvg.onclick = null;
    }

    buildInputNeuron() {
        this.inputSvg = document.createElementNS('http://www.w3.org/2000/svg','svg');
        this.inputLine = document.createElementNS('http://www.w3.org/2000/svg', 'line');
        this.inputSpikeLine = document.createElementNS('http://www.w3.org/2000/svg', 'line');
        this.backgroundLine = document.createElementNS('http://www.w3.org/2000/svg', 'line');
        this.circle = document.createElementNS('http://www.w3.org/2000/svg', 'circle');
        this.spikeCircle = document.createElementNS('http://www.w3.org/2000/svg', 'circle');
        this.backgroundCircle = document.createElementNS('http://www.w3.org/2000/svg', 'circle');

        this.inputSvg.classList.add('inputNeuron');
        this.inputLine.classList.add('inputLine');
        this.inputSpikeLine.classList.add('inputSpikeLine');
        this.backgroundLine.classList.add('inputBackgroundLine');
        this.circle.classList.add('inputCircle');
        this.spikeCircle.classList.add('spikeCircle');
        this.backgroundCircle.classList.add('inputBackgroundCircle');

        let applyLineAttributes = (elmnt) => {
            elmnt.setAttribute('x1', '0');
            elmnt.setAttribute('y1', '25');
            elmnt.setAttribute('x2', '60');
            elmnt.setAttribute('y2', '25');
        }
        let applyCircleAttributes = (elmnt) => {
            elmnt.setAttribute('r', RADIUS);
            elmnt.setAttribute('cx', '60');
            elmnt.setAttribute('cy', '25');
        }

        applyLineAttributes(this.inputLine);
        applyLineAttributes(this.inputSpikeLine);
        applyLineAttributes(this.backgroundLine);
        applyCircleAttributes(this.circle);
        applyCircleAttributes(this.spikeCircle);
        applyCircleAttributes(this.backgroundCircle);
        this.spikeCircle.setAttribute('r', '0');

        this.inputSvg.appendChild(this.backgroundCircle);
        this.inputSvg.appendChild(this.backgroundLine);
        this.inputSvg.appendChild(this.inputLine);
        this.inputSvg.appendChild(this.inputSpikeLine);
        this.inputSvg.appendChild(this.circle);
        this.inputSvg.appendChild(this.spikeCircle);
        ioDiv.appendChild(this.inputSvg);
    }

    oscillate(wait) {
        this.oscillator = setTimeout(() => {
            this.spike(1);
            this.oscillate(wait);
        }, wait);
    }

    stopOscillating() {
        clearTimeout(this.oscillator)
    }
};