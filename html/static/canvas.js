var pitchStage = new Konva.Stage({
    container: 'pitch-box',   // id of container <div>
    width: 200,
    height: 250
});

var pitchLayer = new Konva.Layer();

var pitchAngle = new Konva.Text({
    x: 100,
    y: 250,
    text: '00',
    fontSize: 30,
    fontFamily: 'sans-serif',
    fill: 'black'
});
pitchAngle.offsetX(pitchAngle.width() / 2);
pitchAngle.offsetY(pitchAngle.height());
pitchLayer.add(pitchAngle);

var pitchDegree = new Konva.Text({
    x: 130,
    y: 250,
    text: '°',
    fontSize: 30,
    fontFamily: 'sans-serif',
    fill: 'black'
});
pitchDegree.offsetX(pitchDegree.width());
pitchDegree.offsetY(pitchDegree.height());
pitchLayer.add(pitchDegree);

var imageObj = new Image();
var img;
imageObj.onload = function() {
    img = new Konva.Image({
    x: 0,
    y: 0,
    image: imageObj,
    width: 200,
    height: 200
    });

    pitchLayer.add(img);
};
imageObj.src = '/static/car_angle_bg_alt.svg';

var pitchImgLoader = new Image();
var pitchImg;
pitchImgLoader.onload = function() {
    pitchImg = new Konva.Image({
        x: 100,
        y: 100,
        image: pitchImgLoader,
        width: 200,
        height: 120
    });

    pitchImg.offsetX(pitchImg.width() / 2);
    pitchImg.offsetY(pitchImg.height() / 2);
    pitchLayer.add(pitchImg);
};
pitchImgLoader.src = '/static/car_pitch.svg';
pitchStage.add(pitchLayer);

/* ROLL */

var rollStage = new Konva.Stage({
    container: 'roll-box',   // id of container <div>
    width: 200,
    height: 250
});

var rollLayer = new Konva.Layer();

var rollAngle = new Konva.Text({
    x: 100,
    y: 250,
    text: '00',
    fontSize: 30,
    fontFamily: 'sans-serif',
    fill: 'black'
});
rollAngle.offsetX(rollAngle.width() / 2);
rollAngle.offsetY(rollAngle.height());
rollLayer.add(rollAngle);

var rollDegree = new Konva.Text({
    x: 130,
    y: 250,
    text: '°',
    fontSize: 30,
    fontFamily: 'sans-serif',
    fill: 'black'
});
rollDegree.offsetX(rollDegree.width());
rollDegree.offsetY(rollDegree.height());
rollLayer.add(rollDegree);

var image2Obj = new Image();
var img2;
image2Obj.onload = function() {
    img2 = new Konva.Image({
    x: 0,
    y: 0,
    image: image2Obj,
    width: 200,
    height: 200
    });

    rollLayer.add(img2);
};
image2Obj.src = '/static/car_angle_bg_alt.svg';

var rollImgLoader = new Image();
var rollImg;
rollImgLoader.onload = function() {
    rollImg = new Konva.Image({
        x: 100,
        y: 100,
        image: rollImgLoader,
        width: 200,
        height: 120
    });

    rollImg.offsetX(rollImg.width() / 2);
    rollImg.offsetY(rollImg.height() / 2);
    rollLayer.add(rollImg);
};
rollImgLoader.src = '/static/car_front.svg';
rollStage.add(rollLayer);

var ws = new WebSocket('ws://192.168.4.1/ws');
ws.binaryType = 'arraybuffer';

ws.onmessage = (event) => {
    rollImg.zIndex(3);
    pitchImg.zIndex(3);
    img.zIndex(0);
    img2.zIndex(0);

    var dv = new DataView(event.data);
    
    // Wartości są odwrócone
    let pitch = -Math.round(dv.getInt32(0, true)/10)/10;
    let roll =  -Math.round(dv.getInt32(4, true)/10)/10;
    let reset = dv.getUint8(8, true);

    console.log("Reset: ",reset);
    document.getElementById("test").textContent = reset;

    pitchImg.rotation(pitch);
    rollImg.rotation(roll);

    const pad = (num, size) => {
        var s = "000000000" + num;
        return s.substr(s.length-size);
    }

    pitch = pad(Math.min(Math.abs(Math.round(pitch)), 90), 2);
    roll = pad(Math.min(Math.abs(Math.round(roll)), 90), 2);

    pitchAngle.setAttr('text', pitch);
    rollAngle.setAttr('text', roll);
    
    pitchLayer.draw();
    rollLayer.draw();
}