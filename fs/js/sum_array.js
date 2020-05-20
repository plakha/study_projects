//for...in is intended to look at properties of an object! the usecase here is silly!

function sum(arr) {
    let res = 0;
    for (let i in arr) {
        res += parseInt(arr[i]);
    }

    return res;
}


console.log(sum([1, 2]));