# Thievery
This program optimizes the number of crates that may be removed
from a configuration without upsetting cameras observing the configuration 
To begin, it reads in two integers(r&c) between 1 and 100. This specifies the
length and width of the crate configuration. The following r x c lines are integers
between 0 and 10^9 specifying the height of the [r][c]th stack

The algorithm has three parts. The first part initializes the configuration, and determines the
maximum height of every row and column. Additionally, it theoretically removes every crate from the
configuration except 1 from each stack. So think about as though we have satisfied the	top view camera
and we have a big pile of crates next to the area observed by the camera

The second part involves systematically putting back crates to satisfy the front camera. We start with the first
column maximum. We look down the row maxes for an index where rowmax = colmax. If we find one, we restack the appropriate
number of crates in that location and mark that rowmax camera as satisfied. If we don't find a rowmax=colmax for a given colmax
than we choose an arbitrary empty position that satisfies the cameras. We do this for every colmax.

The final step: Once all the front cameras (colmax) are satisfied, we iterate through our rowmax cameras. For any cameras that are
not satisfied yet, we place an appropriate height stack in an arbitray unused position that satisfies the cameras

When this is done, the crates remaining outside of the camera area are the crates we may take. They are the optimal value.

As a human theif, removing all of the crates as a first step seems incredibly wasteful. However, since we're computers, its
a great way to remove a lot of the complexity from the problem.

I was motivated to try this approach after reading the following quote from "Artificial Inteligence A Modern Approach" Russel & Norvig

In many problems the path to the goal is irrelevant. For example, in the 8-queens problem,
what matters is the final configuration of queens, not the order in which they are added. The
same general property holds for many important applications
