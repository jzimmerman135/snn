const FULL_PROG_BAR = 1;
const LEAK_RATE = 5 / (100 * 5); //leak amount per second
const START_LEFT = 0;

class Neuron {
    constructor() { // initialize default variables
        this.inputs = [];
        this.outputs = [];
        this.value = 0;
        this.threshold = 1;
        this.progBarVal = FULL_PROG_BAR;
        this.output = 0;
        this.buildNeuron();
        this.setDragMode();
        this.leakValue();
    }

    addValue(val) {
        this.setValue(this.value + val);
    }

    setValue(val) { // adjust the neuron value and check for spike
        this.value = max(0,val);
        this.progBarVal = FULL_PROG_BAR - (this.value / this.threshold);
        if (this.value < this.threshold) {
            this.c3.style.transition = "0.2s";
            this.c3.style.strokeDashoffset = this.progBarVal;
        }
        else {
            this.calcOutput();
            this.spike();
            this.output = 0;
            this.value = 0;
        }
    }

    calcOutput() {
        this.output = (this.value);
        console.log(this.output);
        for (let i = 0; i < this.outputs.length; i++) {
            this.outputs[i].sendData(this.output);
        }
    }

    leakValue() {
        this.leakTimer = setTimeout(() => {
            this.setValue(this.value - LEAK_RATE);
            this.leakValue();
        }, 200);
    }

    connectToNeuron(neuron) {
        let newConnection = new Connection(this);
        newConnection.connectTo(neuron);
    }

    setDragMode() {
        this.neuronContainer.style.cursor = "grab";
        this.enableDrag();
    }

    setClickMode() {
        this.neuronContainer.onclick = () => { 
            this.addValue(0.2);
        }
    }

    setConnectMode() {
        this.neuronContainer.onclick = () => {
            new Connection(this);
        }
    }

    setIdleMode() {
        this.neuronContainer.onmousedown = null;
        this.neuronContainer.onclick = null;
        this.neuronContainer.style.cursor = "default";
    }

    getPositionTop() {
        let rect = this.neuronContainer.getBoundingClientRect();
        return rect.top;
    }

    getPositionLeft() {
        let rect = this.neuronContainer.getBoundingClientRect();
        return rect.left;
    }

    getInputPointTop() {
        let rect = this.neuronContainer.getBoundingClientRect();
        return (rect.top - (rect.height / 2)) + 90;
    }

    getInputPointLeft() {
        let rect = this.neuronContainer.getBoundingClientRect();
        return (rect.left + (rect.width / 8));
    }

    getOutputPointTop() {
        let rect = this.neuronContainer.getBoundingClientRect();
        return (rect.top - (rect.height / 2)) + 90;
    }

    getOutputPointLeft() {
        let rect = this.neuronContainer.getBoundingClientRect();
        return (rect.left + (rect.width - rect.width / 8 - 4));
    }

    spike() {
        // spike state
        this.c0.style.strokeWidth = "50";
        this.c1.style.strokeWidth = "35";
        this.c3.style.strokeDashoffset = "0";
        this.c3.style.strokeWidth = "0";
        this.c4.style.strokeWidth = "18";
        this.c5.style.strokeWidth = "4";
        
        setTimeout(() => {
            // return to default state
            this.c0.style.strokeWidth = "40";
            this.c1.style.strokeWidth = "20";
            this.c3.style.transition = "0s";
            this.c3.style.strokeWidth = "6";
            this.c3.style.strokeDashoffset = FULL_PROG_BAR;
            this.c4.style.strokeWidth = "0";
            this.c5.style.strokeWidth = "0";
        }, 300);
    }

    shiftRight(step) {
        var rect = this.neuronContainer.getBoundingClientRect(); 
        let boardRect = board.getBoundingClientRect();
        let rowSize = min(8 , parseInt(boardRect.width / rect.width) - 1);
        let offset = (step % rowSize) * 100;
        this.neuronContainer.style.left = offset + START_LEFT + "px";
        if (step >= rowSize) {
            let START_TOP = board.getBoundingClientRect().top;
            this.neuronContainer.style.top = 100 * parseInt(step / rowSize) + START_TOP + "px";
        }
    }

    enableDrag() {
        var pos1 = 0, pos2 = 0, pos3 = 0, pos4 = 0;
        this.neuronContainer.onmousedown = dragMouseDown;
        var elmnt = this.neuronContainer;
        let _this = this;
        function dragMouseDown(e) { // Courtesy of W3Schools tutorial
            e = e || window.event;
            e.preventDefault();
            // get the mouse cursor position at startup:
            pos3 = e.clientX;
            pos4 = e.clientY;
            elmnt.style.cursor = "grabbing";
            document.onmouseup = closeDragElement;
            // call a function whenever the cursor moves:
            document.onmousemove = elementDrag;
        }
        function elementDrag(e) {
            e = e || window.event;
            e.preventDefault();
            // calculate the new cursor position:
            pos1 = pos3 - e.clientX;
            pos2 = pos4 - e.clientY;
            inBounds(pos1, pos2);
            pos3 = e.clientX;
            pos4 = e.clientY;
        
            // set the element's new position:
            elmnt.style.top = (elmnt.offsetTop - pos2) + "px";
            elmnt.style.left = (elmnt.offsetLeft - pos1) + "px";
            for (let i = 0; i < _this.inputs.length; i++) {
                _this.inputs[i].reshape();
            }
            for (let i = 0; i < _this.outputs.length; i++) {
                _this.outputs[i].reshape();
            }
        }
    
        function closeDragElement() {
            // stop moving when mouse button is released:
            document.onmouseup = null; 
            document.onmousemove = null;
            elmnt.style.cursor = "grab";
        }
    
        function inBounds(x, y) {
            if (x && y) {
                x++;
                y++;
            }
            return;
        }
    }

    buildNeuron() { // procedural neuron svg construction
        this.neuronContainer = document.createElement('div');
        this.neuronContainer.className = 'ndiv';

        this.neuronSvg = document.createElementNS('http://www.w3.org/2000/svg', 'svg');
        this.select = document.createElementNS('http://www.w3.org/2000/svg', 'path');
        this.c0 = document.createElementNS('http://www.w3.org/2000/svg', 'circle');
        this.c1 = document.createElementNS('http://www.w3.org/2000/svg', 'circle');
        this.c2 = document.createElementNS('http://www.w3.org/2000/svg', 'circle');
        this.c3 = document.createElementNS('http://www.w3.org/2000/svg', 'circle');
        this.c4 = document.createElementNS('http://www.w3.org/2000/svg', 'circle');
        this.c5 = document.createElementNS('http://www.w3.org/2000/svg', 'circle');
        
        this.neuronSvg.classList.add('neuron');

        this.select.setAttribute('d', 'M 5 25 Q 5 5, 25 5 M 155 5 Q 175 5, 175 25 M 175 155 Q 175 175, 155 175M 5 155 Q 5 175, 25 175');
        function addCircleAttributes(elmnt) {
            elmnt.setAttribute('r', '50');
            elmnt.setAttribute('cx', '90');
            elmnt.setAttribute('cy', '90');
            elmnt.setAttribute('pathLength', '1');
        }
        addCircleAttributes(this.c0);
        addCircleAttributes(this.c1);
        addCircleAttributes(this.c2);
        addCircleAttributes(this.c3);
        addCircleAttributes(this.c4);
        addCircleAttributes(this.c5);

        this.select.classList.add('select');
        this.c0.classList.add('c0'); // outermost darkest blue
        this.c1.classList.add('c1'); // middle blue
        this.c2.classList.add('c2'); // lightest blue
        this.c3.classList.add('c3'); // progress bar turquoise
        this.c4.classList.add('c4'); // spike glow, hidden normally
        this.c5.classList.add('c5'); // spike white, hidden normally

        this.neuronSvg.appendChild(this.select);
        this.neuronSvg.appendChild(this.c0);
        this.neuronSvg.appendChild(this.c1);
        this.neuronSvg.appendChild(this.c2);
        this.neuronSvg.appendChild(this.c3);
        this.neuronSvg.appendChild(this.c4);
        this.neuronSvg.appendChild(this.c5);

        this.neuronContainer.appendChild(this.neuronSvg);
        board.appendChild(this.neuronContainer);

        this.neuronContainer.style.left = START_LEFT + "px";
        this.neuronContainer.style.top = board.getBoundingClientRect().top + "px";
    }
};