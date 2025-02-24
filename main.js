const { app, BrowserWindow } = require('electron')

app.on('ready', () => {
    const win = new BrowserWindow({
        width: 850,
        height: 650,
        autoHideMenuBar: true,
        // alwaysOnTop: true,
        // x: 0,
        // y: 0
    })

    win.loadFile('./pages/index/index.html')
})
