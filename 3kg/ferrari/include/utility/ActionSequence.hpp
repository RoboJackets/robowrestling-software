#ifndef ACTION_SEQUENCE_H
#define ACTION_SEQUENCE_H

#include <vector>
#include <functional>

class ActionSequence {
    private:

        /**
         * will repeat the sequence of actions when done if true.
         */
        bool loop;

        /**
         * if true, will restart action when revisited, if false will
         * pick up where life off.
         */
        bool restart;

        /**
         * pointer to millis().
         */
        int *currentTime;

        /**
         * used with restart parameter.
         */
        int exitTime;
        struct Action {
            std::function<void()> operation; // Function pointer (or callable object)
            int duration;                    // Duration for this action in milliseconds
        };
        std::vector<Action> actions;
    public:
        ActionSequence(bool loopSequence, bool restartSequence, int *currentTimePtr);
        void addAction(void *operation(), int duration);
        void executeAction();

};

#endif