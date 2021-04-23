const express = require("express")
const app = express()


app.use(express.static("../lab04"))

app.get("/index",(req,res)=>{
    let q =req.query;
    let response = {
        "LED1"    :[q.LED1,q.LED2,q.LED3,q.LED4],
        "on&off"  : q.Switch,
     }
    response.LED1.forEach((e,i) => {
        if(e == "true")
            controlLED(i+1,q.Switch);
    });
    res.send(response);
});
app.get("/index1",(req,res)=>{
    let q =req.query;
    shine(parseInt(q.frequency));
    res.status(200).send("good");
});


let controlLED=(LED,Switch)=>{

    let child_process =require("child_process");
    let process = child_process.execFile('sudo',["../lab02/gpio",LED,Switch]);
    console.log('sudo',["../lab02/gpio",LED,Switch]);
    process.stdout.on('data',(data)=>{
        console.log(`stdout: ${data}`);
    });
    process.stderr.on('data',(data)=>{
        console.error(`stdout: ${data}`);
    });
}


let shine=(times)=>{
    let child_process =require("child_process");
    let process = child_process.execFile('sudo',["../lab02/gpio3",times]);
    // exec(times);
    //let p = child_process.execFile(times);
    
    process.stdout.on('data',(data)=>{
        console.log(`stdout: ${data}`);
    });
    process.stderr.on('data',(data)=>{
        console.error(`stdout: ${data}`);
    });
    
}

// set port,listen for requests
const PORT = process.env.PORT || 8080;
app.listen(PORT,()=>{
    console.log(`Server is running on port ${PORT}.`);
});