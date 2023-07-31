#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include <vector>
#include <algorithm>

using namespace std;
class DomainChecker;

class Domain {
	friend DomainChecker;
public:
	// разработайте класс домена
	// конструктор должен позволять конструирование из string, с сигнатурой определитесь сами
	Domain(const string& input) : domain_string(input){
		int first = 0;
		int last = 0;
		for (const char& ch : domain_string) {
			if (ch != '.') {
				++last;
			}
			else {
				domains.emplace_back(&domain_string.at(first), last - first);
				++last;
				first = last;
			}
		}
		if (first != last) {
			domains.emplace_back(&domain_string.at(first), last - first);
		}
	}

	// operator=
	Domain& operator=(const Domain& input) {
		if (this == &input) {
			return *this;
		}
		domain_string = input.domain_string;
		domains = input.domains;
		return *this;
	}

	/*
	// operator<
	bool operator<(const Domain& input) const {
		return domain_string < input.domain_string;
	}
	*/

	// разработайте operator==
	bool operator==(const Domain& input) const {
		return domain_string == input.domain_string;
	}
	// разработайте метод IsSubdomain, принимающий другой домен и возвращающий true, если this его поддомен
	bool IsSubdomain(const Domain& input) const {
		if (this->domains.size() <= input.domains.size()) return false;
		for (int i = this->domains.size() - 1, j = input.domains.size() - 1; i >= 0 && j >= 0; --i, --j) {
			if (domains.at(i) != input.domains.at(j)) return false;
		}
		return true;
	}
private:
	string domain_string;
	vector<string_view> domains;
};

class DomainChecker {

public:
	// конструктор должен принимать список запрещённых доменов через пару итераторов
	template <typename Iterator>
	DomainChecker(Iterator begin, Iterator end) : forbidden_domains(begin, end) {
		sort(forbidden_domains.begin(), forbidden_domains.end(), [](const Domain& lhs, const Domain& rhs) {
			return std::lexicographical_compare(lhs.domains.rbegin(), lhs.domains.rend(), rhs.domains.rbegin(), rhs.domains.rend());
			});
		auto last = unique(forbidden_domains.begin(), forbidden_domains.end(), [](const Domain& lhs, const Domain& rhs) {
			return rhs.IsSubdomain(lhs);
			});
		forbidden_domains.erase(last, forbidden_domains.end());
	}
	// разработайте метод IsForbidden, возвращающий true, если домен запрещён
	bool IsForbidden(const Domain& input) {
		if (input.domains.size() == 0) return true;
		if (forbidden_domains.size() == 0) return false;

		auto iter = std::lower_bound(forbidden_domains.begin(), forbidden_domains.end(), input, [](const Domain& lhs, const Domain& rhs) {
			return std::lexicographical_compare(lhs.domains.rbegin(), lhs.domains.rend(), rhs.domains.rbegin(), rhs.domains.rend());
			});
		if (iter == forbidden_domains.end()) {
			return input.IsSubdomain(*(iter - 1));
		};
		if (*iter == input) return true;
		if (iter == forbidden_domains.begin()) {
			return input.IsSubdomain(*(iter));
		}
		else {
			return input.IsSubdomain(*(iter - 1));
		}
	}
private:
	std::vector<Domain> forbidden_domains;
};

// разработайте функцию ReadDomains, читающую заданное количество доменов из стандартного входа
template <typename Number>
const std::vector<Domain> ReadDomains(std::istream& input, Number num) {
	std::vector<Domain> result;
	result.reserve(num);
	string line = "";
	for (Number i = 0; i < num; ++i)
	{
		if (getline(input, line)) {
			result.emplace_back(line);
		}
	}
	return result;
}

template <typename Number>
Number ReadNumberOnLine(istream& input) {
	string line;
	getline(input, line);

	Number num;
	std::istringstream(line) >> num;

	return num;
}

int main() {
	const std::vector<Domain> forbidden_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
	DomainChecker checker(forbidden_domains.begin(), forbidden_domains.end());

	const std::vector<Domain> test_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
	for (const Domain& domain : test_domains) {
		cout << (checker.IsForbidden(domain) ? "Bad"sv : "Good"sv) << endl;
	}
}