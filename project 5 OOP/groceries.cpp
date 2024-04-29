#include <fstream>
#include <sstream>
#include <iostream>
#include <list>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "split.h"
using namespace std;

//////////////////
// Customer code /
//////////////////
struct Customer {
  int cust_id;
  string name;
  string street;
  string city;
  string state;
  string zip;
  string phone;
  string email;
  Customer(int id, const string& name, const string& street, const string& city,
  const string& state, const string& zip, const string& phone, const string& email)
  : name(name), street(street), city(city), state(state), zip(zip), phone(phone), email(email) 
  {
    cust_id = id;
  }
  string print_detail() const {
    return "Customer ID #" + to_string(cust_id) + ":\n" +
    name + ", ph. " + phone + ", email: " + email + "\n" +
    street + "\n" +
    city + ", " + state + " " + zip;
  }
};
vector<Customer> customers;

void read_customers(const string& fname) {
  ifstream cust;
  cust.open(fname);
  if (!cust.is_open()) {
    cout << "Could not open file customers.txt." << endl;
    return;
  }
  string line;
  while(getline(cust, line)) {
    auto data = split(line, ',');
    Customer c(stoi(data[0]), data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
    customers.push_back(c);
  }
  cust.close();
}

int find_cust_idx(int cust_id) {
  for (int i = 0; i < customers.size(); ++i)
    if (cust_id == customers[i].cust_id)
      return i;
  throw runtime_error("Customer not found");
}

//////////////
// Item code /
//////////////
struct Item {
  int item_id;
  string description;
  double price;
  Item(int id, const string& desc, double pric) : description(desc) {
    item_id = id;
    price = pric;
  }
};
vector<Item> items;

void read_items(const string& fname) {
  ifstream ite;
  ite.open(fname);
  if (!ite.is_open()) {
    cout << "Could not open file items.txt." << endl;
    return;
  }
  string line;
  while(getline(ite, line)) {
    auto data = split(line, ',');
    Item i(stoi(data[0]), data[1], stod(data[2]));
    items.push_back(i);
  }
  ite.close();
}

int find_item_idx(int item_id) {
  for (int i = 0; i < items.size(); ++i)
    if (item_id == items[i].item_id)
      return i;
  throw runtime_error("Item not found");
}

class LineItem {
  int item_id;
  int qty;
  friend class Order;
public:
  LineItem(int id, int q) {
    item_id = id;
    qty = q;
  }
  double sub_total() const {
    int idx = find_item_idx(item_id);
    return items[idx].price * qty;
  }
  friend bool operator<(const LineItem& item1, const LineItem& item2) {
    return item1.item_id < item2.item_id;
  }
};

/////////////////
// Payment code /
/////////////////
class Payment {
  double amount = 0.0;
  friend class Order;
public:
  Payment() = default;
  virtual ~Payment() = default;
  virtual string print_detail() const = 0;
};

class Credit : public Payment {
  string cardNum;
  string expiration;
public:
  Credit(const string& cnum, const string& exp) : cardNum(cnum), expiration(exp) {}
  string print_detail() const override {
    return "Paid by Credit card " + cardNum + ", exp. " + expiration;
  }
};

class Paypal : public Payment {
  string paypal_id;
public:
  Paypal(const string& papa_id) : paypal_id(papa_id) {}
  string print_detail() const override {
    return "Paid by Paypal ID: " + paypal_id;
  }
};

class WireTransfer : public Payment {
  string bank_id;
  string account_id;
public:
  WireTransfer(const string& b_id, const string& a_id) : bank_id(b_id), account_id(a_id) {}
  string print_detail() const override {
    return "Paid by Wire transfer from Bank ID " + bank_id + ", Account# " + account_id;
  }
};

///////////////
// Order code /
///////////////
class Order {
  int order_id;
  string order_date;
  int cust_id;
  vector<LineItem> line_items;
  Payment* payment;
public:
  Order(int id, const string& date, int c_id, const vector<LineItem>& items, Payment* p) 
  : order_date(date), line_items(items) {
    order_id = id;
    cust_id = c_id;
    payment = p;
    sort(line_items.begin(), line_items.end());
    // Compute order_total
    double total = 0;
    for (LineItem item : line_items) {
      total += item.sub_total();
    }
    payment->amount = total;
  }
  ~Order() {
    delete payment;
  }
  double total() const {
    return payment->amount;
  }
  string print_order() const {
    int custInd = find_cust_idx(cust_id);
    ostringstream orderInfo;
    orderInfo << "===========================" << endl;
    //order id and date
    orderInfo << "Order #" << order_id << ", Date: " << order_date << endl;
    //billing info
    orderInfo << "Amount: $" << total() << ", " << payment->print_detail() << endl << endl;
    //add customer info
    orderInfo << customers[custInd].print_detail() << endl << endl;
    //add all line items, qty, description, and price
    orderInfo << "Order Detail:" << endl;
    for (LineItem item : line_items) {
      int itemInd = find_item_idx(item.item_id);
      orderInfo << "\tItem " << item.item_id << ": \"" << items[itemInd].description << "\", " << item.qty << " @ " << fixed << setprecision(2) << items[itemInd].price << endl;
    }
    return orderInfo.str(); //return stringstream as string
  }
};
list<Order> orders;

void read_orders(const string& fname) {
  ifstream orderf(fname);
  string line;
  while (getline(orderf, line)) {
    // split line
    auto data = split(line, ',');
    // Extract cust_id, order_id, and date
    int cust_id = stoi(data[0]);
    int order_id = stoi(data[1]);
    string date = data[2];
    // Create line item vector
    vector<LineItem> line_items;

    for (size_t i = 3; i < data.size(); i++) { //i = 3 to skip first lines
      auto itemData = split(data[i], '-');
      LineItem li(stoi(itemData[0]), stoi(itemData[1])); //id, qty
      line_items.push_back(li);
    }
    sort(begin(line_items), end(line_items));
    
    // Read payment method (by reading/splitting next line in file)
    getline(orderf, line);
    vector<string> payData;
    if (orderf.fail()) {
      // reading next line failed
      cout << "could not read second line of order" << endl;
    }
    else {
      payData = split(line, ',');
    }
    // Create concrete Payment object on heap (pmt)
    Payment* pmt;

    switch (stoi(payData[0])) {
      case 1: //credit card
        pmt = new Credit(payData[1], payData[2]);
        break;
      case 2: //PayPal
        pmt = new Paypal(payData[1]);
        break;
      case 3: //wire transfer
        pmt = new WireTransfer(payData[1], payData[2]);
        break;
      default:
        cout << "invalid payment type found." << endl;
    }
    //place in list
    orders.emplace_back(order_id, date, cust_id, line_items, pmt);
  }
  orderf.close();
}

int main() {
  read_customers("customers.txt");
  read_items("items.txt");
  read_orders("orders.txt");

  ofstream ofs("order_report.txt");
  for (const Order& order: orders)
    ofs << order.print_order() << endl;

  ofs.close();
}
