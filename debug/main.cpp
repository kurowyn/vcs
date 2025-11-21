#include <QApplication>
#include <QWidget>
#include <QString>
#include <print>

int main(int argc, char **argv) {
    if (argc != 4) {
        std::println("usage: ./main (width) (height) (title)");
        std::exit(1);
    }
    auto width {std::stoi(argv[1])}, height {std::stoi(argv[2])};
    auto title {argv[3]};

    QApplication app {argc, argv};

    QWidget w {};

    w.setWindowTitle(title);
    w.resize(width, height);
    w.show();

    return app.exec();
}
