# Problem 5

The pipline pattern would suffice as a `TopicServer` alternative by making use of the `BoundedBuffers` class, as detailed in Figure 4.17. In the context of the problem, the lack of concurrency results from the synchronous nature of the receive method for `TopicServer,` which can be resolved by placing the messages into a buffer as invoked by successive calls of receive. Setting `TopicServer` to a loop means that a message can be retrieved and sent to a waiting subscriber, allowing both operation to run concurrently.
