const { app, BrowserWindow, ipcMain, screen } = require('electron')
const path = require('path');

let mainWindow;
let timerWindow;

// 窗口位置同步函数
function positionTimerWindow() {
  if (!mainWindow || mainWindow.isDestroyed()) return;
  if (!timerWindow || timerWindow.isDestroyed()) return;

  const mainBounds = mainWindow.getBounds();
  const display = screen.getDisplayMatching(mainBounds).workArea;

  // 设置计时器窗口位置
  timerWindow.setBounds({
    x: mainBounds.x,
    y: mainBounds.y + mainBounds.height + 5, // 主窗口下方5像素
    width: mainBounds.width,
    height: 150
  });

  // 边界检查防止超出屏幕
  const timerBounds = timerWindow.getBounds();
  if (timerBounds.y + timerBounds.height > display.y + display.height) {
    timerWindow.setPosition(
      timerBounds.x,
      display.y + display.height - timerBounds.height
    );
  }
}

function createWindows() {
  // 主窗口配置
  mainWindow = new BrowserWindow({
    width: 1000,
    height: 800,
    alwaysOnTop: true,
    autoHideMenuBar: true,
    icon: path.join(__dirname, './geek-s-puzzle.png'),
    webPreferences: {
      nodeIntegration: true,
      contextIsolation: false
    }
  });

  // 计时器窗口配置
  timerWindow = new BrowserWindow({
    width: 1000,
    height: 150,
    transparent: true,
    frame: false,
    alwaysOnTop: true,
    show: false, // 先隐藏等待定位
    webPreferences: {
      nodeIntegration: true,
      contextIsolation: false
    },
    icon: path.join(__dirname, './geek-s-puzzle.png')
  });

  // 加载页面
  mainWindow.loadFile('./pages/index/start.html');
  timerWindow.loadFile('./pages/index/timer.html');

  // 窗口就绪后定位
  mainWindow.on('ready-to-show', () => {
    positionTimerWindow();
    timerWindow.show();
  });

  // 监听窗口事件
  ['move', 'resize', 'maximize'].forEach(event => {
    mainWindow.on(event, () => {
      positionTimerWindow();
      // 解决最大化时的显示问题
      if (mainWindow.isMaximized()) {
        timerWindow.setFullScreenable(false);
      }
    });
  });

  // 处理最小化状态
  mainWindow.on('minimize', () => timerWindow.hide());
  mainWindow.on('restore', () => timerWindow.show());

  // 导航到finish.html的处理
  mainWindow.webContents.on('did-navigate', (event, url) => {
    if (url.endsWith('finish.html')) {
      timerWindow.webContents.send('stop-timer');
    }
  });

  // 窗口关闭处理
  mainWindow.on('closed', () => {
    if (timerWindow && !timerWindow.isDestroyed()) {
      timerWindow.destroy();
    }
  });
}

// 进程通信处理
ipcMain.on('timer-stopped', () => {
  if (timerWindow && !timerWindow.isDestroyed()) {
    timerWindow.webContents.send('trigger-fireworks');
  }
});

app.whenReady().then(createWindows);