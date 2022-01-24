
const CONNECTION_START_COLOR = '#b83a3a';
class Connection {
    constructor(neuron) { //pass from neuron in constructor
        this.from = neuron;
        this.to = null;
        this.value = null;
        this.weight = 0.25;
        this.isGood = false;
        this.delay = 0.75;
        this.buildNewConnection();
    }

    setToNeuron(neuron) {
        this.to = neuron;
    }

    makeSVG() {   
        this.thickLine = document.createElementNS('http://www.w3.org/2000/svg', 'line');
        this.line = document.createElementNS('http://www.w3.org/2000/svg', 'line');

        this.line.classList.add('lweight');
        this.setAttributesToZero(this.thickLine);

        connectionSvg.appendChild(this.line);
        connectionSvg.appendChild(this.thickLine);    
    }

    buildNewConnection() {
        this.makeSVG();
        let rect = board.getBoundingClientRect();
        this.line.setAttribute('x1', this.from.getOutputPointLeft() - rect.left);
        this.line.setAttribute('y1', this.from.getOutputPointTop() - rect.top);
        this.line.setAttribute('x2', this.from.getOutputPointLeft() - rect.left);
        this.line.setAttribute('y2', this.from.getOutputPointTop() - rect.top);
        this.line.style.stroke = '#283593';
        
        document.onmousemove = () => { this.dragEnd() };

        for (let i = 0; i < neurons.length; i++) {
            if (neurons[i] == this.from) {
                neurons[i].neuronContainer.onclick = null;
            }
            else {
                neurons[i].neuronContainer.onclick = () => {
                    if (!this.willBeDuplicate(neurons[i])) {
                        this.connectTo(neurons[i]);
                        connectMode();
                    }
                }
            }
        }

        for (let i = 0; i < inputNeurons.length; i++) {
            inputNeurons[i].inputSvg.onclick = null;
        }

        document.onclick = (e) => { // delete on click elsewhere
            e = e || window.event;
            let targetClass = e.target.className.baseVal;
            if (targetClass == 'lweight' || targetClass == 'connectionSVG') {
                this.deleteConnection();
                connectMode();
            }
        }

        window.onkeydown = (e) => { // delete connection on esc key
            e = e || window.event;
            if (e.keyCode == 27) { 
                this.deleteConnection();
            }
        }
    }

    connectTo(neuron) {
        if (this.from == neuron) {
            return;
        }
        this.deleteConnection();
        this.makeSVG();
        this.to = neuron;
        this.reshape();

        this.isGood = true;

        this.from.outputs.push(this);
        this.to.inputs.push(this);
        connections.push(this);
    }

    reshape() {
        let rect = board.getBoundingClientRect();

        let x1 = this.from.getOutputPointLeft() - rect.left;
        let y1 = this.from.getOutputPointTop() - rect.top;

        let x2 = this.to.getInputPointLeft() - rect.left;
        let y2 = this.to.getInputPointTop() - rect.top;
     
        this.setLinePoints(this.thickLine, x1, y1, x2, y2);
        this.setLinePoints(this.line, x1, y1, x2, y2);
    }

    dragEnd(e) {
        e = e || window.event;
        let rect = board.getBoundingClientRect();
        this.line.setAttribute('x2', e.clientX - rect.left);
        this.line.setAttribute('y2', e.clientY - rect.top);
    }

    deleteConnection() {
        document.onmousemove = null;
        document.onclick = null;
        window.onkeydown = null;
        
        this.thickLine.remove();
        this.line.remove();
        
        if (this.isGood) {
            let i = this.from.outputs.indexOf(this);
            let j = this.to.inputs.indexOf(this);
            let k = connections.indexOf(this);
            this.from.outputs.splice(i, 1);
            this.to.inputs.splice(j, 1);
            connections.splice(k, 1);
        }
    }

    async sendData(val, className=false) {
        let spikeLine = document.createElementNS('http://www.w3.org/2000/svg', 'line');
        this.setAttributesToZero(spikeLine);
        spikeLine.classList.add('lspike');
        if (className) {
            spikeLine.classList.replace('lspike',className);
        }
        spikeLine.setAttribute('pathLength','1');
        connectionSvg.appendChild(spikeLine);

        this.value = val * this.weight;
        this.sendDataLerpElmnt(spikeLine);
        setTimeout(() => {
            this.to.addValue(this.value);
        }, this.delay * 1000);
        return;
    }

    // must have this.value set to correct amount
    sendDataLerpElmnt(elmnt) {
        let _this = this;
        let framerate = 60;
        let transition = this.delay * 1000;
        
        let startX = this.line.x1.baseVal.value;
        let startY = this.line.y1.baseVal.value;
        let finalX = this.line.x2.baseVal.value;
        let finalY = this.line.y2.baseVal.value;

        let x1, y1, x2, y2, t1, t2;
        let t = 0;
        let w = this.value * 120 / Math.sqrt(Math.pow(finalX - startX, 2) + Math.pow(finalY - startY, 2)); //width as a percentage of the total length of line
        this.setLinePoints(elmnt, startX, startY, startX, startY);
        
        timedLoop();

        function timedLoop() {
            setTimeout(() => {
                adjustEnds();
                t += 1 / (_this.delay * framerate);
                t1 = max(0, t - w);
                t2 = min(1, t);

                x1 = (1 - t1) * startX + t1 * finalX;
                y1 = (1 - t1) * startY + t1 * finalY;
                x2 = (1 - t2) * startX + t2 * finalX;
                y2 = (1 - t2) * startY + t2 * finalY;

                _this.setLinePoints(elmnt, x1, y1, x2, y2);
                
                if (t > 1 + w){
                    elmnt.remove();
                    return;
                }
                timedLoop();
            }, transition / framerate);
        }

        async function adjustEnds() {
            startX = _this.line.x1.baseVal.value;
            startY = _this.line.y1.baseVal.value;
            finalX = _this.line.x2.baseVal.value;
            finalY = _this.line.y2.baseVal.value;
        }
    }

    setLinePoints(elmnt, x1, y1, x2, y2) {
        elmnt.setAttribute('x1', x1);
        elmnt.setAttribute('y1', y1);
        elmnt.setAttribute('x2', x2);
        elmnt.setAttribute('y2', y2);
    }

    setAttributesToZero(elmnt) {
        elmnt.setAttribute('x1', 0);
        elmnt.setAttribute('y1', 0);
        elmnt.setAttribute('x2', 0);
        elmnt.setAttribute('y2', 0);
    }

    setClickMode() {
        this.thickLine.classList.add('lthick');
        this.thickLine.onclick = () => {
            this.sendData(1);
        }
    }

    setCutMode() {
        this.thickLine.classList.add('lhighlight');
        this.thickLine.onmouseenter = () => {
            this.line.style.strokeDasharray = 8;
            this.thickLine.onmouseleave = () => {
                this.line.style.strokeDasharray = 0;
            }
        }
        this.thickLine.onclick = () => {
            this.deleteConnection();
        }
    }

    setIdleMode() {
        this.thickLine.classList.remove('lthick', 'lhighlight');
        this.thickLine.onclick = null;
        this.thickLine.onmouseenter = null;
        if (!this.isGood) {
            this.deleteConnection();
        }
    }

    willBeDuplicate(to) {
        for (let i = 0; i < to.inputs.length; i++) {
            if (to.inputs[i].from == this.from) {
                return true;
            }
        }
        return false;
    }
};