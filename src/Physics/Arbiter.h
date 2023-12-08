#pragma once

struct Body;
class Contact;

struct Arbiter
{
    // Connectivity
    Body*       a;
    Body*       b;

    // Combined Friction
    float       friction;

    // Run-time Data
    Contact     contacts[2];
    int         numContacts;

    Arbiter(Body* a, Body* b) : a(a), b(b) {}
};

struct ArbiterKey
{
    Body*       a;
    Body*       b;

    ArbiterKey(Body* a, Body* b) : a(a), b(b) {}
};

