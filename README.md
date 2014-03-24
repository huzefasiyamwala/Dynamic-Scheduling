Dynamic-Scheduling
==================

To solve Heterogneous Assignment with probability problems, wherein no of tasks needs to be completed within deadline for mission critical systems. For each task, input data is
 
              P1                      P2
        T    C     P            T     C     P
        1    8    0.3           2     6     0.6
        3    8    1.0           4     6     1.0
----------------------------------------------------------------
Here P1, P2 represents no. of processor on which this task can be scheduled
T - Indicates time during which it can be completed with P probabilty
P - Probabilty that this task will be completed.
C - Cost for scheduling this task on a particular processor

For systems wherein task dependencies arises like
   T1---->T2----> T3

Task T3 cannot be started unless both task T1 and T2 are completed. For this kind of DAG(Directed Acyclic Graph), algorithms schedules all these task on all available processors such that total cost is minimised with high level of confidence probability.
