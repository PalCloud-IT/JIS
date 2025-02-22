/* Simple Sentiment Analysis in C */
#include <stdio.h>
#include <string.h>

#define POSITIVE_WORDS 5
#define NEGATIVE_WORDS 5

const char *positive[POSITIVE_WORDS] = {"happy", "great", "good", "love", "excellent"};
const char *negative[NEGATIVE_WORDS] = {"sad", "bad", "terrible", "hate", "awful"};

int analyze_sentiment(const char *message) {
    int score = 0;
    for (int i = 0; i < POSITIVE_WORDS; i++) {
        if (strstr(message, positive[i]) != NULL) {
            score++;
        }
    }
    for (int i = 0; i < NEGATIVE_WORDS; i++) {
        if (strstr(message, negative[i]) != NULL) {
            score--;
        }
    }
    return score;
}

int main() {
    char message[256];
    printf("Enter a message: ");
    fgets(message, sizeof(message), stdin);
    
    int sentiment_score = analyze_sentiment(message);
    if (sentiment_score > 0) {
        printf("The message has a positive sentiment.\n");
    } else if (sentiment_score < 0) {
        printf("The message has a negative sentiment.\n");
    } else {
        printf("The message has a neutral sentiment.\n");
    }
    return 0;
}
