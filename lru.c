#include <stdio.h>

int main() {
    int n, f;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    
    int pages[n];
    printf("Enter the page reference string: ");
    for(int i=0;i<n;i++)
        scanf("%d",&pages[i]);

    printf("Enter number of frames: ");
    scanf("%d",&f);

    int frames[f], counter[f];
    for(int i=0;i<f;i++){
        frames[i]=-1; // empty frame
        counter[i]=0;
    }

    int faults=0, time=0;

    printf("\nPage\tFrames\n-----------------\n");

    for(int i=0;i<n;i++){
        time++;
        int page=pages[i], found=0;

        // Check if page is already in frames
        for(int j=0;j<f;j++){
            if(frames[j]==page){
                counter[j]=time; // Update last used time
                found=1;
                break;
            }
        }

        if(!found){
            faults++;
            int lru_index=0;

            // Find empty frame
            for(int j=0;j<f;j++){
                if(frames[j]==-1){
                    lru_index=j;
                    break;
                }
            }

            // If all frames full, find LRU page
            if(frames[lru_index]!=-1){
                int min=counter[0];
                lru_index=0;
                for(int j=1;j<f;j++){
                    if(counter[j]<min){
                        min=counter[j];
                        lru_index=j;
                    }
                }
            }

            frames[lru_index]=page;
            counter[lru_index]=time;
        }

        // Display current frames
        printf("%d\t",page);
        for(int j=0;j<f;j++){
            if(frames[j]!=-1) printf("%d ",frames[j]);
            else printf("- ");
        }
        printf("\n");
    }

    printf("-----------------\nTotal Page Faults = %d\n",faults);
    return 0;
}
