struct Process {
    char* name;
    long arrival;
    long cpu;
    long IO_count;
    long priority;
    long lastRunTime;
    long cpu_remaining;
    long IO_remaining;
    long IO_interval;
    long IO_operations;
    long IO_complete;
    long next_io_time;
    long completion_time;
    int time_until_io;
};
