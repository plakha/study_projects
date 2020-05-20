function newCounter() {
  // eslint-disable-next-line no-underscore-dangle
  let _counter = 0;

  return {
    field: 'asdgswadf',
    increment() {
      _counter += 1;
    },
    decrement() {
      _counter -= 1;
    },
    value() {
      return _counter;
    },
  };
}

const counter1 = newCounter();
const counter2 = newCounter();

counter1.increment();
counter1.value();
counter2.value();
