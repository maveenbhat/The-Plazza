// # Lib Imports

#include <string.h>
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h>
#include <sys/wait.h>

// # Local Imports

#include "../include/Engine.hpp"

// # Static values

static const char *error_usage = "Bad usage.\n";
static const char *error_multiplier = "Multiplier "
    "value must be a positive number.\n";
static const char *error_cooks = "Cooks value "
    "must be a positive number.\n";
static const char *error_refresh = "Cooks value "
    "must be a positive number.\n";

static const char *s_usage = "-h";
static const char *sec_usage = "-help";

// # Methods

static bool usage(int ac, char **as)
{
    if (ac != 2
        || (strcmp(as[1], s_usage)
        && strcmp(as[1], sec_usage)))
        return (false);
    std::cout << "USAGE:" << std::endl;
    std::cout << "\t    " << as[0] << " [multiplier] [cooks] [time]" << std::endl;
    std::cout << "DESCRIPTION:" << std::endl;
    std::cout << "\t    multiplier\t" << "multiplier for "
        << "the cooking time of the pizzas" << std::endl;
    std::cout << "\t    cooks\t" << "number of cooks per kitchen" << std::endl;
    std::cout << "\t    time\t" << "the time in milliseconds, " <<
        "used by the kitchen stock to replace ingredients" << std::endl;
}

static bool check(int ac, char **as)
{
    if (ac != 4) {
        std::cerr << error_usage;
        return (false);
    } else if (atoi(as[1]) <= 0) {
        std::cerr << error_multiplier;
        return (false);
    }
    if (atoi(as[2]) <= 0) {
        std::cerr << error_cooks;
        return (false);
    } else if (atoi(as[3]) <= 0) {
        std::cerr << error_refresh;
        return (false);
    }
    return (true);
}

int main(int ac, char **as)
{
    const int success = 0;
    const int fail = 84;
    Engine *engine = NULL;
    commu_t *commu;
    int pid = fork();
    int memid = shmget(0x00042473, sizeof(commu_t), 0700 | IPC_CREAT);

    if (memid < 0)
        return (fail);
    commu = (commu_t *)shmat(memid, NULL, 0);
    if (pid < 0)
        return (fail);
    else if (pid == 0) {
        if (!engine)
            exit(84);
        engine->check_kitchens();
        engine->display();
        engine->running = true;
        exit(0);
    } else {
        if (usage(ac, as))
            return (success);
        if (!check(ac, as))
            return (fail);
        engine = new Engine(
            atoi(as[1]),
            atoi(as[2]),
            atoi(as[3])
        );
        engine->commu = commu;
        if (!engine)
            return (fail);
        engine->run();
        delete(engine);
        wait(NULL);
    }
    return (success);
}
