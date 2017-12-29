#include <iostream>
#include <vector>
#include <string>

std::vector<int> longest_prefix_suffix(const std::string& pattern) {
    int i, len;
    std::vector<int> lps = std::vector<int>(pattern.size());
    std::fill_n(lps.begin(), lps.size(), 0);

    // length of the longest previous prefix and suffix
    len = 0;
    i = 1;

    while (i < pattern.size()) {
        // comparison always starts from 0
        if (pattern[i] == pattern[len]) {
            len += 1;
            lps[i] = len;
            i += 1;
        } else {
            if (len == 0) {
                // previous length = 0 and current character does not match
                // increment i (implicitly set lps[i] to 0)
                i += 1;
            } else {
                // previous length != 0 and current character does not match
                // decrease length (do not update i) and see if there's a match

                /*
                 *  Suppose we are trying to compute the longest prefix suffix array (lps) for the following pattern:
                 *  \begin{equation*}
                 *      a_0, a_1, \cdots, a_{-1}, a^\star
                 *  \end{equation*}
                 *  Let's further suppose that $\text{lps}[-2] = m$, i.e., $"a_0, \cdots, a_{m-1}"$ is the same as $"a_{-m}, \cdots, a_{-1}"$ and $a_m != a^\star$. Now, because $a_m != a^\star$, we should decrease the length that we are trying to match, in particular, according to the algorithm we set $\text{len} = \text{lps}[m-1]$ \footnote{Note that we can not simply update len by $\text{len} = \text{len} - 1$ because the resulting match position is not the same. Consider the pattern "acaacc", using the update rule just mentioned will result in incorrect value for the last position.}. Note that we know the following:
                 *  \begin{align*}
                 *          a_0 & = a_{-m}\\
                 *          a_1 & = a_{-(m-1)}\\
                 *          & \cdots\\
                 *          a_{m-1} & = a_{-1}
                 *  \end{align*}
                 *  Now suppose that $\text{lps}[m-1] = l$, we know the following:
                 *  \begin{align*}
                 *          a_0 & = a_{m-l}\\
                 *          a_1 & = a_{m-l+1}\\
                 *          & \cdots\\
                 *          a_{l-1} & = a_{m-1}
                 *  \end{align*}
                 *  Therefore, we have the following:
                 *  \begin{align*}
                 *          a_{0} & = a_{-l}\\
                 *          a_{l-2} & = a_{-2}\\
                 *          & \cdots\\
                 *          a_{l-1} & = a_{-1}
                 *  \end{align*}
                 *  Because of the above, we can safely continue matching from $\text{pat}[l] == a^\star$
                 */
                len = lps[len-1];
            }
        }
    }

    return lps;
}

int main() {
    std::string test_pattern = "aaabaaa";
    std::vector<int> result = longest_prefix_suffix(test_pattern);
    for (std::vector<int>::iterator it = result.begin(); it != result.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}