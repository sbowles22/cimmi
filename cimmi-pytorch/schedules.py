
"""
All schedules are based off of a normalized//unitless schedule time
"""

def schedule_constant(p = 1.1):
    _schedule = lambda t: 1.1
    return _schedule

def schedule_linear(slope = 0.1, t_mid = 1.0, p_mid = 1.0, max_val = None):
    _schedule = lambda t: min(slope * (t - t_mid) + p_mid, 
                              max_val if max_val else float('inf'))
    return _schedule
