#ifndef ACTION_SEQUENCE_H
#define ACTION_SEQUENCE_H

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
    public:

        void addAction(void *operation(), int duration);
        void executeAction();

};

#endif