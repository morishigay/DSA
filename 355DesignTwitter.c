//LEETCODE 355: DESIGN TWITTER
#include <stdlib.h>

typedef struct Tweet{
    int tweetId;
    int userId;
    struct Tweet* userNext;
    struct Tweet* globalNext;
} Tweet;

typedef struct User{
    int userId;
    int followingCount;
    Tweet* tweets;
    struct User* next;
} User;

typedef struct Twitter{
    int userId;
    int tweetId;
    User* users;
    Tweet* tweets;
} Twitter;

User* createUser(int userId){
    User* user = (User*)malloc(sizeof(User));
    user->userId = userId;
    user->followingCount = 0;
    user->next = NULL;
    return user;
}

Tweet* createTweet(int tweetId){
    Tweet* tweet = (Tweet*)malloc(sizeof(Tweet));
    return tweet;
}

Twitter* createTwitter(){

}

void twitterPostTweet(Twitter* obj, int userId, int tweetId) {
    //get user first
    User* user = obj->users;
    while (user != NULL && user->userId != userId){ //while user is not null and user's id is not the one we're looking for, we keep traversing
        user = user->next;
    }

    if (user == NULL){ //if we reached the end of the list/ user is not found, we create a new user
        User* user  = (User*)malloc(sizeof(User));
        user->userId = userId;
        user->followingCount = 0;
        user->tweets = NULL;
        user->next = obj->users;
        obj->users = user;
    }

    //then create tweet and add to user's tweet list
    Tweet* tweet = (Tweet*)malloc(sizeof(Tweet));
    tweet->tweetId = tweetId;
    tweet->userId = userId;
    tweet->userNext = user->tweets;
    user->tweets = tweet;

    //add tweet to global tweet list too
    tweet->globalNext = obj->tweets;
    obj->tweets = tweet;

    //what now? this is a void function
}
int* twitterGetNewsFeed(Twitter* obj, int userId, int* retSize) {
    //get user's tweets and follower's tweets


    //return tweet ids in order


    //
}

void twitterFollow(Twitter* obj, int followerId, int followeeId) {
    //check if fo
}

void twitterUnfollow(Twitter* obj, int followerId, int followeeId) {
    //
}

void twitterFree(Twitter* obj) {
    free(obj->users);
    free(obj->tweets);
    free(obj);
}

int main(){
    return 0;
}
