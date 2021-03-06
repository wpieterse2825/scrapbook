void ConsoleBuffer_Start();
void ConsoleBuffer_Stop();
void ConsoleBuffer_Frame();

void ConsoleSystem_Start();
void ConsoleSystem_Stop();
void ConsoleSystem_Frame();
void ConsoleSystem_Error(const char* error_message);
void ConsoleSystem_Print(const char* message);
void ConsoleSystem_Show();
void ConsoleSystem_Hide();

void ConsoleGame_Start();
void ConsoleGame_Stop();
void ConsoleGame_Frame();
void ConsoleGame_Print(const char* message);

void Variable_Start();
void Variable_Stop();
void Variable_Frame();

void Command_Start();
void Command_Stop();
void Command_Frame();
bool Command_CallConsole(const char* line);
