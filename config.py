def can_build(env, platform):
    return True

def get_opts(platform):
    from SCons.Variables import BoolVariable

    # Tracy on demand
    #You should note that if on-demand profiling is disabled (which is the default), then the recorded events
    #will be stored in the system memory until a server connection is made and the data can be uploaded11.
    #Depending on the amount of the things profiled, the requirements for event storage can quickly grow up to a
    #couple of gigabytes. Furthermore, since this data is no longer available after the initial connection, you won’t
    #be able to perform a second connection to a client unless the on-demand mode is used.

    #Caveats
    #The client with on-demand profiling enabled needs to perform additional bookkeeping to present a
    #coherent application state to the profiler. This incurs additional time costs for each profiling event.

    return [
        BoolVariable("tracy_on_demand", "Enable profiling only when there’s an established connection with the server", False),
    ]

def configure(env):
    pass
