#include <QApplication>
#include <QDir>
#include <QVBoxLayout>
#include <QListWidget>
#include <QStackedWidget>
#include "../include/Home_Page.h"
#include "../include/Adb_Utils.h"
#include "../include/Script_Page.h"

int main(int argc, char *argv[]) {
    // Adb_Utils adb("C:/Users/86133/Desktop/Auto1999cpp/cmake-build-debug/platform-tools/adb.exe","16384");
    // adb.adb_connect_device();
    // adb.get_adb_device();
    // adb.close_adb();
    QDir appDir = QDir(QCoreApplication::applicationDirPath());
    QString scriptsPath = appDir.filePath("scripts");

    if (!appDir.exists("scripts")) {
        if (appDir.mkdir("scripts")) {
            qInfo() << "[INFO]" << "Created scripts/ directory.";
        } else {
            qWarning() << "[WARNING]" << "Failed to create scripts/ directory!";
        }
    } else {
        qInfo() << "[INFO]" << "scripts/ directory already exists.";
    }

    QApplication app(argc, argv);

    QWidget window;
    // QVBoxLayout *layout = new QVBoxLayout(&window);
    //
    // Home_Page *home_page = new Home_Page(&window);
    // layout->addWidget(home_page);
    //
    // window.resize(960, 540);
    // window.show();

    QHBoxLayout main_layout = QHBoxLayout();

    QListWidget *nav_list = new QListWidget();
    nav_list->addItem("首页");
    nav_list->addItem("脚本");
    nav_list->setFixedWidth(100);

    QStackedWidget *stack = new QStackedWidget();
    stack->addWidget(new Home_Page(stack));
    stack->addWidget(new Script_Page(stack));

    QObject::connect(nav_list,&QListWidget::currentRowChanged,stack,&QStackedWidget::setCurrentIndex);

    nav_list->setCurrentRow(0);

    main_layout.addWidget(nav_list);
    main_layout.addWidget(stack);

    window.setLayout(&main_layout);
    window.resize(1060,675);
    window.show();

    return app.exec();
}

// #include <QApplication>
// #include <QWidget>
// #include <QVBoxLayout>
// #include <QHBoxLayout>
// #include <QGroupBox>
// #include <QLabel>
// #include <QScrollArea>
//
// // 创建一个节点（带标题和可选描述）
// QGroupBox *createNode(const QString &title, const QString &detail = QString()) {
//     QGroupBox *box = new QGroupBox(title);
//     QVBoxLayout *layout = new QVBoxLayout(box);
//     if (!detail.isEmpty())
//         layout->addWidget(new QLabel(detail));
//     return box;
// }
//
// // 创建分支1，含嵌套判断和分支
// QVBoxLayout *createBranch1() {
//     QVBoxLayout *branch1 = new QVBoxLayout;
//     branch1->addWidget(createNode("分支1-步骤1", "分支1的第一个操作"));
//     branch1->addWidget(createNode("分支1-步骤2", "分支1的第二个操作"));
//
//     // 嵌套判断
//     branch1->addWidget(createNode("分支1-判断", "分支1中的判断节点"));
//
//     QHBoxLayout *subBranchLayout = new QHBoxLayout;
//     // 子分支1-1
//     QVBoxLayout *sub1 = new QVBoxLayout;
//     sub1->addWidget(createNode("分支1-1-步骤1"));
//     sub1->addWidget(createNode("分支1-1-结束"));
//     subBranchLayout->addLayout(sub1);
//
//     // 子分支1-2
//     QVBoxLayout *sub2 = new QVBoxLayout;
//     sub2->addWidget(createNode("分支1-2-步骤1"));
//     sub2->addWidget(createNode("分支1-2-步骤2"));
//     sub2->addWidget(createNode("分支1-2-结束"));
//     subBranchLayout->addLayout(sub2);
//
//     branch1->addLayout(subBranchLayout);
//
//     branch1->addWidget(createNode("分支1-合流", "分支1合流后继续"));
//     branch1->addWidget(createNode("分支1-结束"));
//     return branch1;
// }
//
// // 创建分支2
// QVBoxLayout *createBranch2() {
//     QVBoxLayout *branch2 = new QVBoxLayout;
//     branch2->addWidget(createNode("分支2-步骤1"));
//     branch2->addWidget(createNode("分支2-结束"));
//     return branch2;
// }
//
// // 创建分支3
// QVBoxLayout *createBranch3() {
//     QVBoxLayout *branch3 = new QVBoxLayout;
//     branch3->addWidget(createNode("分支3-步骤1"));
//     branch3->addWidget(createNode("分支3-步骤2"));
//     branch3->addWidget(createNode("分支3-结束"));
//     return branch3;
// }
//
// int main(int argc, char *argv[]) {
//     QApplication app(argc, argv);
//
//     QWidget *flowWidget = new QWidget;
//     QVBoxLayout *mainLayout = new QVBoxLayout(flowWidget);
//
//     // 主流程
//     mainLayout->addWidget(createNode("步骤1：启动应用", "通过ADB启动目标App"));
//     mainLayout->addWidget(createNode("步骤2：等待加载", "等待3秒"));
//     mainLayout->addWidget(createNode("步骤3：登录", "输入账号密码并登录"));
//     mainLayout->addWidget(createNode("步骤4：进入主界面", "检测主界面元素"));
//     mainLayout->addWidget(createNode("步骤5：判断", "是否检测到按钮？"));
//
//     // 分支
//     QHBoxLayout *branchLayout = new QHBoxLayout;
//     branchLayout->addLayout(createBranch1());
//     branchLayout->addLayout(createBranch2());
//     branchLayout->addLayout(createBranch3());
//     mainLayout->addLayout(branchLayout);
//
//     // 分支后合流
//     mainLayout->addWidget(createNode("步骤6：分支合流", "所有分支后继续主流程"));
//     mainLayout->addWidget(createNode("步骤7：执行每日任务1"));
//     mainLayout->addWidget(createNode("步骤8：执行每日任务2"));
//     mainLayout->addWidget(createNode("步骤9：流程结束"));
//
//     // 滚动区域
//     QScrollArea *scrollArea = new QScrollArea;
//     scrollArea->setWidget(flowWidget);
//     scrollArea->setWidgetResizable(true);
//
//     QWidget window;
//     QVBoxLayout *windowLayout = new QVBoxLayout(&window);
//     windowLayout->addWidget(scrollArea);
//
//     window.setWindowTitle("复杂流程嵌套分支示例");
//     window.resize(1200, 900);
//     window.show();
//
//     return app.exec();
// }
