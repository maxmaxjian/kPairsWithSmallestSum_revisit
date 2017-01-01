#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <iterator>

namespace std {
    std::ostream & operator<<(std::ostream & os, const std::pair<size_t,size_t> & pr) {
        os << "(" << pr.first << "," << pr.second << ")";
        return os;
    }
}

class solution {
public:
    std::vector<std::pair<int,int>> kPairsWithSmallestSum(const std::vector<int> & nums1, const std::vector<int> & nums2, int k) {
        std::vector<std::pair<size_t,size_t>> path{std::make_pair(0,0)};
        while (path.size() < size_t(k))
            path = addOne(nums1, nums2, path);
        std::copy(path.begin(), path.end(), std::ostream_iterator<std::pair<size_t,size_t>>(std::cout, " "));
        std::cout << std::endl;

        std::vector<std::pair<int,int>> result;
        std::transform(path.begin(), path.end(), std::inserter(result, result.begin()),
                       [&](const std::pair<size_t,size_t> & pr){
                           return std::make_pair(nums1[pr.first], nums2[pr.second]);
                       });
        return result;
    }

private:
    std::vector<std::pair<size_t,size_t>> addOne(const std::vector<int> & nums1, const std::vector<int> & nums2, const std::vector<std::pair<size_t,size_t>> & curr) {
        std::vector<std::pair<size_t,size_t>> result(curr);
        std::pair<size_t,size_t> next = getNext(nums1, nums2, curr);
        if (next.first != 0 || next.second != 0) {
            result.push_back(next);
        }
        return result;
    }

    std::pair<size_t,size_t> getNext(const std::vector<int> & nums1, const std::vector<int> & nums2, const std::vector<std::pair<size_t,size_t>> & curr) {
        std::vector<std::pair<size_t,size_t>> cands;
        if (curr.back() == std::make_pair(nums1.size()-1, nums2.size()-1))
            return std::make_pair(0,0);
        else {
            // if (curr.back().first == nums1.size()-1)
            //     return std::make_pair(curr.back().first, curr.back().second+1);
            // else if (curr.back().second == nums2.size()-1)
            //     return std::make_pair(curr.back().first+1, curr.back().second);
            // else {
            //     auto it = std::find_if(nums2.begin(), nums2.begin()+curr.back().second+2, 
            //                            [&](int i2){
            //                                return nums1[curr.back().first+1]+nums2[i2] >= nums1[curr.back().first]+nums2[curr.back().second];
            //                            });
            //     cands.push_back(std::make_pair(curr.back().first+1, std::distance(nums2.begin(),it)));

            //     it = std::find_if(nums1.begin(), nums1.begin()+curr.back().first+2,
            //                       [&](int i1){
            //                           return nums1[i1]+nums2[curr.back().second+1] >= nums1[curr.back().first]+nums2[curr.back().second];
            //                       });
            //     cands.push_back(std::make_pair(std::distance(nums1.begin(), it), curr.back().second+1));
            // }

	    for(size_t i = 0; i <= curr.back().first; i++) {
		for (size_t j = curr.back().second+1; j < nums2.size(); j++) {
		    if (nums1[i]+nums2[j] >= nums1[curr.back().first]+nums2[curr.back().second])
			cands.push_back(std::make_pair(i,j));
		}
	    }

	    for (size_t j = 0; j <= curr.back().second; j++) {
		for (size_t i = curr.back().first; i < nums1.size(); i++) {
		    if (nums1[i]+nums2[j] >= nums1[curr.back().first]+nums2[curr.back().second])
			cands.push_back(std::make_pair(i,j));
		}
	    }

	    auto it = cands.begin();
	    while (it != cands.end()) {
		if (std::find(curr.begin(), curr.end(), *it) != curr.end())
		    it = cands.erase(it);
		else
		    ++it;
	    }

            return *std::min_element(cands.begin(), cands.end(),
                                     [&](const std::pair<size_t,size_t> p1, const std::pair<size_t,size_t> & p2){
                                         return nums1[p1.first]+nums2[p1.second] < nums1[p2.first]+nums2[p2.second];
                                     });
        }
    }
};

int main() {
    // std::vector<int> nums1{1,7,11}, nums2{2,4,6};
    // int k = 3;

    std::vector<int> nums1{1,1,2}, nums2{1,2,3};
    int k = 9;

    solution soln;
    auto pairs = soln.kPairsWithSmallestSum(nums1, nums2, k);
    std::cout << "The " << k << " smallest pairs are:\n";
    std::copy(pairs.begin(), pairs.end(), std::ostream_iterator<std::pair<int,int>>(std::cout, " "));
    std::cout << std::endl;
}
