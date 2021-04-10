// © Guillaume COQUARD, April 2018


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>


/*
States :
- B : birth
- A : awake
- D : death
- S : sleep
- O : orphan
- Z : zombie

  B   Z       O			process_id = M-ZZZ-XXX
  B 	    S   O Z		process_id = M-ZZZ-YYY
 B-- S   A   Z 			process_id = M-ZZZ
M--                     process_id = M

*/


int main()
{
	pid_t pid_XXX, pid_YYY, pid_ZZZ;
	pid_ZZZ = fork(); // Fork Main =========================== / M-ZZZ-[B]
	if (pid_ZZZ > 0) // Act in Main ========================== / M-[A]
	{
		while (1)
		{
			sleep(1000); // Make Sleep Main ================== / M-[S]
		}
	}
	else if (pid_ZZZ == 0) // Act in Zombie ================== / M-ZZZ-[A]
	{
		pid_YYY = fork(); // Create Orphan-Zombie ============ / M-ZZZ-YYY-[B]
		if (pid_YYY > 0) // Act in Zombie ==================== / M-ZZZ-[A]
		{
			pid_XXX = fork(); // Create Zombie-Orphan ======== / M-ZZZ-XXX-[B]
			if (pid_XXX > 0) // Act in Zombie ================ / M-ZZZ-[A]
			{
				sleep(10); // Make Sleep Zombie ============== / M-ZZZ-[S]
			}
			else if (pid_XXX == 0) // Act in Zombie-Orphan === / M-ZZZ-XXX-[A]
			{
				exit(EXIT_SUCCESS); // Death ================= / M-ZZZ-XXX-[D;Z]
			}
		}
		if (pid_YYY == 0) // Act in Orphan-Zombie Child ====== / M-ZZZ-YYY-[A]
		{
			sleep(10); // Make Sleep Orphan-Zombie ============= / M-ZZZ-YYY-[S]
		}
		kill(getpgid(getpid())+1,SIGKILL); // Death ========== / M-ZZZ-[D;Z]
		// State of Zombie-Orphan ============================ / M-ZZZ-XXX-[Z;O]
		// State of Orphan-Zombie ============================ / M-ZZZ-YYY-[S;O]
		if (pid_YYY == 0) // ================================= / M-ZZZ-YYY-[O]
		{
			exit(EXIT_SUCCESS); // =========================== / M-ZZZ-YYY-[O;D;Z]
		}
	}
	return (0);
}
