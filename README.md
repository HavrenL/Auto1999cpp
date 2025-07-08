# Auto1999cpp

## 项目简介
Auto1999cpp 是一个基于 Qt 的自动化脚本管理与设备控制工具，支持脚本的创建、导入、管理以及通过 ADB/Scrcpy 控制安卓设备。项目由本人独立开发，使用 JetBrains CLion 作为主要开发环境。

## 主要功能
- 脚本的创建、导入、删除与信息管理
- 通过 ADB 连接、管理安卓设备
- 集成 Scrcpy 实现设备画面捕获与嵌入
- 友好的图形化界面，支持多脚本管理

## 依赖环境
- Qt 6.x（推荐 Qt 6.5 及以上）
- C++17 或更高
- ADB 工具（Android Debug Bridge）
- Scrcpy 工具
- 开发环境：JetBrains CLion

## 目录结构
```
Auto1999cpp/
├── src/                # 源码目录
├── include/            # 头文件目录
├── scripts/            # 脚本存放目录（自动生成）
├── CMakeLists.txt      # CMake 构建脚本
└── README.md           # 项目说明文档
```

## 开发计划 / 待完善内容
- 图像识别与点击相关功能（如自动定位、模拟点击等）
- 脚本流程的可视化（流程控制可视化）
- 更美观、现代的 UI 界面
- 其他细节优化与功能完善

## 许可证
本项目采用 MIT License 开源。 