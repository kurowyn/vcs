#include <raylib.h>
#include <print>
#include <thread>

bool g_is_time_up = false;

void DoGameStuff(void) {
    auto current_time {std::chrono::steady_clock::now()};
    SetTraceLogLevel(LOG_FATAL);
    InitWindow(200, 200, "Bad Simulator");
    while (!g_is_time_up) {
        BeginDrawing();
        ClearBackground((Color){0, 0, 0, 0xaa});
        DrawRectangle(0, 0, 100, 100, (Color){0xff, 0, 0, 0xff});
        DrawRectangle(50, 50, 100, 100, (Color){0, 0xff, 0, 0xdd});
        DrawRectangle(100, 100, 100, 100, (Color){0, 0, 0xff, 0xaa});
        EndDrawing();
    }
    CloseWindow();
}

void CountTime(int duration) {
    using namespace std::chrono_literals;
    do {
        std::println("[INFO] Remaining seconds: {}", duration);
        std::this_thread::sleep_for(1s);
    } while (--duration != 0);
    g_is_time_up = true;
    std::println("[INFO] Finished! If all goes well, you should have no window!");
}

int main(void) {
    auto game_thread {std::thread{DoGameStuff}};

    auto timer_thread {std::thread{CountTime, 5}};

    game_thread.join();
    timer_thread.join();

    return 0;
}
