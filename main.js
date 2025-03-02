const { app, BrowserWindow } = require('electron')
const path = require('path');

app.on('ready', () => {
    const win = new BrowserWindow({
        width: 850,
        height: 650,
        autoHideMenuBar: true,
        icon: path.join(__dirname,'./geek-s-puzzle.png'),
        // alwaysOnTop: true,
        // x: 0,
        // y: 0
    })

    win.loadURL("https://geek-s-puzzle-alpha.axa6.com/?track=alpha-app")
    // win.loadFile('./pages/index/task9.html')
})
