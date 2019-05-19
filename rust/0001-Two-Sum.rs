use std::collections::HashMap;

struct Solution;

impl Solution {
    pub fn two_sum(nums: Vec<i32>, target: i32) -> Vec<i32> {
        let mut map = HashMap::new();
        let mut res = vec![-1, -1];
        for i in 0..nums.len() {
            let val = target - nums[i];
            match map.get(&val) {
                None => map.insert(nums[i], i),
                _ => {
                    res[0] = *map.get(&val).unwrap() as i32;
                    res[1] = i as i32;
                    return res;
                }
            };
        }
        res
    }
}

fn main() {
    let nums = vec![2, 7, 11, 15];
    let target: i32 = 9;

    let res = Solution::two_sum(nums, target);

    println!("[{}, {}]", res[0], res[1]);
}