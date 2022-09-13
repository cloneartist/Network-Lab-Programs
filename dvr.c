#include <stdio.h>
int dist[50][50], temp[50][50], n, i, j, k;
void dvr()
{
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            for (k = 0; k < n; k++)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    temp[i][j] = k;
                }

    for (i = 0; i < n; i++)
    {
        printf("\n\nState value for router %d is \n", i + 1);
        for (j = 0; j < n; j++)
            printf("\t\nnode %d via %d Distance%d", j + 1, temp[i][j] + 1, dist[i][j]);
    }
    printf("\n\n");
}
int main()
{
    printf("\nEnter the number of nodes : ");
    scanf("%d", &n);
    printf("\nEnter the distance matrix :\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &dist[i][j]);
            dist[i][i] = 0;
            temp[i][j] = j;
        }
        printf("\n");
    }
    dvr();
    return 0;
}

// #include <stdio.h>
// int main()
// {
//     int n, count;
//     printf("Enter the number of nodes:");
//     scanf("%d", &n);
//     int c[n][n];
//     printf("Enter the cost matrix of the nodes:\n  ");
//     for (int i = 0; i < n; i++)
//     {
//         printf("%d ", i + 1);
//     }
//     printf("\n");
//     for (int i = 0; i < n; i++)
//     {
//         printf("%d ", i + 1);
//         for (int j = 0; j < n; j++)
//         {
//             scanf("%d", &c[i][j]);
//         }
//     }
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = 0; j < n; j++)
//         {
//             if (i == j)
//             {

//                 continue;
//             }
//             else
//             {
//                 for (int k = 0; k < n; k++)
//                 {
//                     if (c[i][j] > c[i][k] + c[i][k])
//                     {
//                         c[k][j] = c[i][j] + c[i][k];
//                     }
//                 }
//             }
//         }
//     }
//     printf("The final routing table is: \n  ");
//     for (int i = 0; i < n; i++)
//     {
//         printf("%d ", i + 1);
//     }
//     printf("\n");
//     for (int i = 0; i < n; i++)
//     {
//         printf("%d ", i + 1);
//         for (int j = 0; j < n; j++)
//         {
//             printf("%d ", c[i][j]);
//         }
//         printf("\n");
//     }

//     // for (int i = 0; i < n; i++)
//     // {
//     //     printf("State value of router %d", i + 1);
//     //     for (int j = 0; j < n; j++)
//     //     {
//     //         printf("Node %d via %d is %d", j + 1, j + 1, c[i][j]);
//     //         printf("\n");
//     //     }
//     //     printf("\n");
//     // }
// }