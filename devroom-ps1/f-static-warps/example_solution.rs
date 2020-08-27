/*
    제 1회 개발자 수다방 PS 대회 공식 답안 : F번 - 총통의 축지법
    작성자 : quickn <quickwshell@gmail.com>
    적용된 이론 : Matroid, Greedy
    시간 복잡도 (Time complexity) : O(MNlogN)
    공간 복잡도 (Space complexity) : O(N + M)
*/

use std::io::{self, BufWriter, Write};

mod scanner {
    use std::{io, str};
    /* https://github.com/EbTech/rust-algorithms */

    /// Same API as Scanner but nearly twice as fast, using horribly unsafe dark arts
    /// **REQUIRES** Rust 1.34 or higher
    pub struct UnsafeScanner<R> {
        reader: R,
        buf_str: Vec<u8>,
        buf_iter: str::SplitAsciiWhitespace<'static>,
    }

    impl<R: io::BufRead> UnsafeScanner<R> {
        pub fn new(reader: R) -> Self {
            Self {
                reader,
                buf_str: Vec::new(),
                buf_iter: "".split_ascii_whitespace(),
            }
        }

        /// This function should be marked unsafe, but noone has time for that in a
        /// programming contest. Use at your own risk!
        pub fn token<T: str::FromStr>(&mut self) -> T {
            loop {
                if let Some(token) = self.buf_iter.next() {
                    return token.parse().ok().expect("Failed parse");
                }
                self.buf_str.clear();
                self.reader
                    .read_until(b'\n', &mut self.buf_str)
                    .expect("Failed read");
                self.buf_iter = unsafe {
                    let slice = str::from_utf8_unchecked(&self.buf_str);
                    std::mem::transmute(slice.split_ascii_whitespace())
                }
            }
        }
    }
}

use std::cmp::min;

fn main() {
    let (stdin, stdout) = (io::stdin(), io::stdout());
    let (mut scan, mut sout) = (
        scanner::UnsafeScanner::new(stdin.lock()),
        BufWriter::new(stdout.lock()),
    );
    // 입력을 받는다
    let (n, m): (usize, usize) = (scan.token(), scan.token());
    let mut x_0: Vec<usize> = vec![0; m];
    for i in 0..m {
        x_0[i] = scan.token();
    }
    let mut set: Vec<usize> = vec![0; n];
    for j in 0..n {
        set[j] = j + 1;
    }
    // 메인 로직
    let mut cardinality = std::usize::MAX;
    for i in 0..m {
        // 각 성분별로 나눠서 Maximum weight independent set을 찾는 부분문제를 해결한다.
        let mut set_i = set.clone();
        set_i.sort_by(|&x, &y| {
            let d1 = ((x as isize) - (x_0[i] as isize)).abs();
            let d2 = ((y as isize) - (x_0[i] as isize)).abs();
            d1.cmp(&d2)
        });
        set_i.reverse();
        let mut ans: Vec<usize> = Vec::new();
        let mut basis: [usize; 32] = [0; 32];
        // 입력 제한이 2^31 미만이므로 그 미만의 값에 대해서
        // XOR 값을 효율적이게 계산하게 하려는 부분이다.
        for k in 0..31 {
            let k_inv = 31 - k - 1;
            if (x_0[i] >> k_inv) & 1 != 0 {
                basis[k_inv] = x_0[i];
                ans.push(x_0[i]);
                break;
            }
        }
        for j in 0..n {
            if set_i[j] != x_0[i] {
                let mut xor_res = set_i[j];
                for k in 0..31 {
                    let k_inv = 31 - k - 1;
                    if (xor_res >> k_inv) & 1 != 0 {
                        xor_res ^= basis[k_inv];
                        if (xor_res >> k_inv) & 1 != 0 {
                            basis[k_inv] = xor_res;
                            ans.push(set_i[j]);
                            break;
                        }
                    }
                }
            }
        }
        // i) 나중에 결국 가장 작은 크기의 indendent set만 합쳐질 것이다.
        // ii) 문제 조건에서 euclidean distance의 제곱이라고 했으니 역시 순서에도 무관하니 그냥 합치면 된다.
        cardinality = min(cardinality, ans.len());
    }
    // 출력 부분
    writeln!(sout, "{}", cardinality).ok();
}