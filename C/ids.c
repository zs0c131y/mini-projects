#include <stdio.h>
#include <windows.h>
#include <time.h>

#define CPU_THRESHOLD 80.0    // CPU usage threshold in percentage
#define MEMORY_THRESHOLD 80.0 // Memory usage threshold in percentage

double get_cpu_usage()
{
    FILETIME idleTime, kernelTime, userTime;
    ULONGLONG idle, kernel, user;
    double cpuUsage;

    if (!GetSystemTimes(&idleTime, &kernelTime, &userTime))
    {
        fprintf(stderr, "Error: Unable to get system times.\n");
        return -1.0;
    }

    idle = ((ULONGLONG)idleTime.dwHighDateTime << 32) | idleTime.dwLowDateTime;
    kernel = ((ULONGLONG)kernelTime.dwHighDateTime << 32) | kernelTime.dwLowDateTime;
    user = ((ULONGLONG)userTime.dwHighDateTime << 32) | userTime.dwLowDateTime;

    cpuUsage = ((double)(kernel + user - idle) / (kernel + user)) * 100.0;

    return cpuUsage;
}

double get_memory_usage()
{
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(memoryStatus);

    if (!GlobalMemoryStatusEx(&memoryStatus))
    {
        fprintf(stderr, "Error: Unable to get memory status.\n");
        return -1.0;
    }

    double memoryUsage = ((double)(memoryStatus.dwMemoryLoad)) / 100.0 * 100.0;

    return memoryUsage;
}

void log_intrusion(char *message)
{
    FILE *log_file = fopen("intrusion_log.txt", "a");
    if (log_file == NULL)
    {
        fprintf(stderr, "Error opening log file.\n");
        return;
    }

    time_t current_time;
    char *c_time_string;

    current_time = time(NULL);
    c_time_string = ctime(&current_time);

    fprintf(log_file, "[%s] %s\n", c_time_string, message);
    fclose(log_file);
}

int main()
{
    printf("Starting Intrusion Detection System...\n");

    // Start system monitoring
    while (1)
    {
        double cpu_usage = get_cpu_usage();
        double memory_usage = get_memory_usage();

        if (cpu_usage > CPU_THRESHOLD)
        {
            printf("High CPU Usage detected: %.2f%%\n", cpu_usage);
            log_intrusion("High CPU Usage detected");
        }

        else
        {
            log_intrusion("Normal CPU Usage\n");
        }

        if (memory_usage > MEMORY_THRESHOLD)
        {
            printf("High Memory Usage detected: %.2f%%\n", memory_usage);
            log_intrusion("High Memory Usage detected");
        }

        else
        {
            log_intrusion("Normal Memory Usage\n");
        }

        Sleep(5000); // Sleep for 5 seconds before checking again
    }

    return 0;
}
