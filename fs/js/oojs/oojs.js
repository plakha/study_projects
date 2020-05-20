(function () {
  function Person(name) {
    this.name = name;
    this.greeting = function () {
      alert(`Hi, my name is ${name} !`)
    };
  }

  const bob = new Person('Bob');
  bob.greeting();
}());
