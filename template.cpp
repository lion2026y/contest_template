#ifdef __LOCAL
  #include "my.h"
#else
  #ifdef __clang__
    #pragma clang fp contract(fast)
    #pragma clang fp reassociate(on)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wunqualified-std-cast-call"
    #pragma clang diagnostic ignored "-Wunused-const-variable"
    #pragma clang diagnostic ignored "-Wsign-compare"
  #elifdef __GNUC__               // gcc用.clangでもgnucは定義されている.
    #pragma GCC optimize("Ofast") //(2 or 3 or fast)
    #pragma GCC optimize("unroll-loops")
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wsign-compare"
  #endif
  #include <atcoder/all>
  #include <bits/stdc++.h>
  #include <execution>
  #include <immintrin.h>
#endif

using namespace std;
namespace rg = std::ranges;
namespace vw = std::ranges::views;
using namespace atcoder;
using atcoder::internal::safe_mod;

using ll = long long;
using ull = uint64_t;
using ld = long double;
using str = string;

// #define int ll //int main()->signed main()に変更.

constexpr int MOD = 998244353;
constexpr auto& cmod(auto& n) { return n %= MOD; }
constexpr int inf = 1001001001;
constexpr ll infl = 1LL << 60;

constexpr char el = '\n', spa = ' ', hs = '#', dot = '.', sma = 'a', bga = 'A', zr = '0';

constexpr int psign(auto const& x) { return x % 2 ? -1 : 1; }
// {左,上,右,下,左上,右上,右下,左下}
constexpr int dr[] = {0, -1, 0, 1, -1, -1, 1, 1}, dc[] = {-1, 0, 1, 0, -1, 1, 1, -1};
constexpr string dir_str = "LURD";

#define rep(i, n) for(int i = 0; i < int(n); ++i)
#define rep2(i, s, n) for(ll i = ll(s); i < ll(n); ++i)
#define rep3(i, s, n, p) for(ll i = ll(s); i < ll(n); i += ll(p))
#define rrep(i, n) for(int i = (n) - 1; i >= 0; --i)

#ifdef __LOCAL
  #define dbg(...) dbgout(__LINE__, '(' + string(#__VA_ARGS__) + ')', __VA_ARGS__)
  #define dbg2(x, ...) [&] { \
    dbgout(__LINE__, '(' + string(#x) __VA_OPT__(+ ", " + string(#__VA_ARGS__)) + ')', \
    x __VA_OPT__(, __VA_ARGS__)); return (x); }() __VA_OPT__(, __VA_ARGS__)
  #define wl cerr << "----------\n"
#else
  #define dbg(...) (void)0
  #define dbg2(...) __VA_ARGS__
  #define wl (void)0
#endif

#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

#define r_iota(i, n, f) views::iota(0, int(n)) | tf(i, f)
#define tf(x, f) views::transform([&]([[maybe_unused]] auto const& x) { return f; }) | ranges::to<vector>()

// clang-format off
inline bool YES() { cout << "YES\n"; return true; }
inline bool NO() { cout << "NO\n"; return false; }
inline bool Yes() { cout << "Yes\n"; return true; }
inline bool No() { cout << "No\n"; return false; }
inline bool yes() { cout << "yes\n"; return true; }
inline bool no() { cout << "no\n"; return false; }
// clang-format on
#define reyes(b) (b ? Yes() : No())

#define fn0(f) [&] { return f; }
#define fn1(f) [&]([[maybe_unused]] auto const& a1) { return f; }
#define fn2(f) [&]([[maybe_unused]] auto const& a1, [[maybe_unused]] auto const& a2) { return f; }

// clang-format off
template<int M>
inline istream& operator>>(istream& i, static_modint<M>& n) { long long t; i >> t; n = t; return i; }
template<int M>
inline ostream& operator<<(ostream& o, static_modint<M> const& n) { return o << n.val(); }
template<int id>
inline istream& operator>>(istream& i, dynamic_modint<id>& n) { long long t; i >> t; n = t; return i; }
template<int id>
inline ostream& operator<<(ostream& o, dynamic_modint<id> const& n) { return o << n.val(); }

template<class T, class U> inline istream& operator>>(istream& i, pair<T, U>& p);
template<class T, class U> inline ostream& operator<<(ostream& o, pair<T, U> const& p);
template<class... Args> inline istream& operator>>(istream& i, tuple<Args...>& t) ;
template<class... Args> inline ostream& operator<<(ostream& o, tuple<Args...> const& t) ;

template<ranges::range R>
struct __ignore_default_range_io: false_type {};

template<ranges::range R>
  requires(ranges::output_range<R, ranges::range_value_t<R>> && !constructible_from<string_view, R>&&
           !__ignore_default_range_io<remove_cvref_t<R>>::value)
inline istream& operator>>(istream& is, R&& r) { for(auto& e: r) is >> e; return is; }
template<ranges::input_range R>
  requires(!constructible_from<string_view, R> && !__ignore_default_range_io<remove_cvref_t<R>>::value)
inline ostream& operator<<(ostream& os, R&& r) {
  auto it = ranges::begin(r); auto end = ranges::end(r);
  if(it == end) return os;
  os << *it++; for(; it != end;) os << ' ' << *it++; return os;
}

template<class T, class U>
inline istream& operator>>(istream& i, pair<T, U>& p) { return i >> p.first >> p.second; }
template<class T, class U>
inline ostream& operator<<(ostream& o, pair<T, U> const& p) { return o << p.first << " " << p.second; }

template<class... Args>
inline istream& operator>>(istream& i, tuple<Args...>& t) {
  return apply([&](Args&... args) -> istream& { return (i >> ... >> args); }, t);
}
template<class... Args>
inline ostream& operator<<(ostream& o, tuple<Args...> const& t) {
  apply([&](Args const&... args) { int i = 0; ((o << (i++ ? " " : "") << args), ...); }, t);
  return o;
}
// clang-format on

// 初期値xのsz*args配列を作成.makev2<T>(x,sz...) Tの非型パラメータが取れないとき.
template<class T, class X>
constexpr T makev2(X const& x) { return x; }
template<class T, class X>
constexpr auto makev2(X const& x, int sz, auto... args) { return vector(sz, makev2<T>(x, args...)); }
// 初期値T{}のsz*args配列を作成.makev<T>(sz,...)
template<class T>
constexpr auto makev(auto... args) { return makev2<T>(T{}, args...); }
// 初期値xのsz*args配列を作成.makev<T,x>(sz,...)
template<class T, T x>
constexpr auto makev(auto... args) { return makev2<T>(x, args...); }

#define vin(type, name, ...) \
  auto name = makev<type>(__VA_ARGS__); \
  cin >> name
template<ostream& os = cerr, ranges::input_range R>
inline void outv(R&& r, string const& s = "\n") {
#ifndef __LOCAL
  if constexpr(&os == &cerr) return;
#endif
  auto it = ranges::begin(r);
  auto end = ranges::end(r);
  if(it == end) return;
  os << *it++;
  for(; it != end;) os << s << *it++;
  os << '\n';
}

// clang-format off
inline void myin(auto&&... args) { (cin >> ... >> args); }

#define iin(...) int __VA_ARGS__; myin(__VA_ARGS__)
#define lin(...) ll __VA_ARGS__; myin(__VA_ARGS__)
#define var(type_name, ...) type_name __VA_ARGS__; myin(__VA_ARGS__)

inline void myout(auto&&... args) { ((cout << args << '\n'), ...); }
inline void myouts(auto&& x, auto&&... args) { cout << x; ((cout << ' ' << args), ...); cout << '\n'; }
inline void myoutc(auto&&... args) { (cout << ... << args); cout << '\n'; }
inline void dbgout(auto&&... args) { ((cerr << args << ' '), ...); cerr << '\n'; }

constexpr bool chmax(auto& a, auto const& b) { if(a < b) { a = b; return true; } return false; }
constexpr bool chmin(auto& a, auto const& b) { if(a > b) { a = b; return true; } return false; }

template<class T> constexpr bool cmax(T& a, T& b) { if(a < b) { swap(a, b); return true; } return false; }
template<class T> constexpr bool cmin(T& a, T& b) { if(a > b) { swap(a, b); return true; } return false; }
// clang-format on

template<class T, class... Args>
constexpr common_type_t<T, Args...> gcd(T&& x, Args&&... args) {
  common_type_t<T, Args...> r = forward<T>(x);
  ([&] { r = std::gcd(r, forward<Args>(args)); }(), ...);
  return r;
}
template<class T, class... Args>
constexpr common_type_t<T, Args...> lcm(T&& x, Args&&... args) {
  common_type_t<T, Args...> r = forward<T>(x);
  ([&] { r = std::lcm(r, forward<Args>(args)); }(), ...);
  return r;
}

// 一つでも[l,r)に含まれない物があるか.
constexpr bool outside(auto const& l, auto const& r, auto const&... args) {
  return ((args < l || r <= args) || ...);
}

// clang-format off
template<class T> struct range_inside { using type = T; static constexpr int count = 0; };
template<ranges::range R> struct range_inside<R> {
  using type = typename range_inside<ranges::range_value_t<R>>::type;
  static constexpr int count = range_inside<ranges::range_value_t<R>>::count + 1;
};
template<class T> using inside_type_t = typename range_inside<T>::type;
template<class T> constexpr int inside_count_t = range_inside<T>::count;
// clang-format on

template<class T>
constexpr T value2(T, T const& x) { return x; }
// r[...]が範囲外ならeを返す value2(e,r,...)でアクセス.非constexpr,テンプレート引数にできない型用.
template<ranges::range R>
constexpr inside_type_t<R> value2(inside_type_t<R> const& e, R const& r, int i, auto... args) {
  if(outside(0, int(ranges::size(r)), i)) return e;
  else return value2(e, r[i], args...);
}
// r[...]が範囲外ならT{}を返す value(r,...)でアクセス.
template<ranges::range R>
constexpr inside_type_t<R> value(R const& r, auto... args) { return value2(inside_type_t<R>{}, r, args...); }
// r[...]が範囲外ならeを返す value<e>(r,...)でアクセス.
template<auto e, ranges::range R>
constexpr inside_type_t<R> value(R const& r, auto... args) { return value2(e, r, args...); }

template<class T1, class T2>
constexpr pair<T1, T2> operator+(pair<T1, T2> const& p1, pair<T1, T2> const& p2) {
  return pair<T1, T2>(p1.first + p2.first, p1.second + p2.second);
}
template<class T1, class T2>
constexpr pair<T1, T2>& operator+=(pair<T1, T2>& p1, pair<T1, T2> const& p2) {
  p1.first += p2.first;
  p1.second += p2.second;
  return p1;
}

// clang-format off
template<class... Args> using vec = vector<Args...>;
template<class... Args> using um = unordered_map<Args...>;
template<class... Args> using us = unordered_set<Args...>;
template<class... Args> using ms = multiset<Args...>;
template<class... Args> using PQ = priority_queue<Args...>;
template<class T> using PQg = priority_queue<T, vector<T>, greater<T>>;
// clang-format on

constexpr void invoke_solve(auto& f) {
  using R = invoke_result_t<decltype(f)>;
  if constexpr(is_void_v<R>) f();
  else if constexpr(same_as<bool, R>) reyes(f());
  else myout(f());
}

constexpr void io_setting() {
  cin.exceptions(ios::badbit | ios::failbit);
  cin.tie(nullptr), ios::sync_with_stdio(false);
#ifdef __LOCAL
  cout << unitbuf;
#endif
  cout << fixed << setprecision(20), cerr << fixed << setprecision(20);
}

using mint = modint998244353;
// using mint = modint1000000007;

using V = vector<int>;
using P = pair<int, int>;
using T = tuple<int, int, int>;
using A = array<int, 2>;

constexpr void solve() {
}

int main() {
  io_setting();
  int _t = 1;
  // cin >> _t;
  while(_t--) invoke_solve(solve);
  // assert(cin.eof() || (cin >> ws && cin.eof() && "still unread"));
  return 0;
}
